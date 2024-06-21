import gymnasium as gym
import numpy as np
import matplotlib.pyplot as plt
import random
from tqdm import tqdm
import torch
from collections import deque
import os
import warnings

warnings.filterwarnings("ignore")

# DQN class to train the agent

class DQN():
    def __init__(self, env, name, gamma=0.99, epsilon=1, epsilon_min=0.02, epsilon_decay=0.999, batch_size=64, lr=1e-3, cuda=False):
        self.env = env
        self.name = name
        self.action_space = env.action_space.n
        self.observation_space = env.observation_space.shape[0]
        self.memory = deque(maxlen=10000)
        self.min_buffer = 10000
        self.gamma = gamma
        self.epsilon = epsilon
        self.epsilon_min = epsilon_min
        self.epsilon_decay = epsilon_decay
        self.batch_size = batch_size
        self.lr = lr
        self.cuda = cuda
        self.model = self.create_model()
        self.target_model = self.create_model()
        self.update_target_model()
        # self.optimizer = torch.optim.Adam(self.model.parameters(), lr=self.lr)
        self.optimizer = torch.optim.RMSprop(self.model.parameters(), lr=self.lr)
        self.scheduler = torch.optim.lr_scheduler.ReduceLROnPlateau(self.optimizer, 'min', patience=0, factor=0.999)
        self.loss = torch.nn.MSELoss()
        if not os.path.exists(f'./{self.name}'):
            os.makedirs(f'./{self.name}')

    def create_model(self):
        if self.name == 'MountainCar':
            model = torch.nn.Sequential(
                torch.nn.Linear(self.observation_space, 64),
                torch.nn.ReLU(),
                torch.nn.Linear(64, 64),
                torch.nn.ReLU(),
                torch.nn.Linear(64, self.action_space)
            )
        elif self.name == 'Pong':
            model = torch.nn.Sequential(
                torch.nn.Conv2d(4, 32, kernel_size=8, stride=4),
                torch.nn.ReLU(),
                torch.nn.Conv2d(32, 64, kernel_size=4, stride=2),
                torch.nn.ReLU(),
                torch.nn.Conv2d(64, 64, kernel_size=3, stride=1),
                torch.nn.ReLU(),
                torch.nn.Flatten(),
                torch.nn.Linear(17408, 512),
                torch.nn.ReLU(),
                torch.nn.Linear(512, self.action_space)
            )
        if self.cuda:
            model.cuda()
        return model

    def update_target_model(self):
        self.target_model.load_state_dict(self.model.state_dict())

    def remember(self, state, action, reward, next_state, terminated, truncated, info):
        self.memory.append([state, action, reward, next_state, terminated, truncated, info])

    def act(self, state):
        if np.random.rand() <= self.epsilon:
            return random.randrange(self.action_space)
        act_values = self.model(torch.Tensor(state).cuda()) if self.cuda else self.model(torch.Tensor(state))
        return torch.argmax(act_values).item()

    def replay(self):
        if len(self.memory) < self.batch_size:
            return
        minibatch = random.sample(self.memory, self.batch_size)
        states, actions, rewards, next_states, terminated, truncated = [], [], [], [], [], []
        for state, action, reward, next_state, termin, truncat, _ in minibatch:
            states.append(state)
            actions.append(action)
            rewards.append(reward)
            next_states.append(next_state)
            terminated.append(termin)
            truncated.append(truncat)

        states = torch.from_numpy(np.array(states).astype(np.float32)).squeeze()
        actions = torch.from_numpy(np.array(actions)).long()
        rewards = torch.from_numpy(np.array(rewards).astype(np.float32))
        next_states = torch.from_numpy(np.array(next_states).astype(np.float32)).squeeze()
        terminated = torch.from_numpy(np.array(terminated)).bool()
        truncated = torch.from_numpy(np.array(truncated)).bool()

        states = states.cuda() if self.cuda else states
        actions = actions.cuda() if self.cuda else actions
        rewards = rewards.cuda() if self.cuda else rewards
        next_states = next_states.cuda() if self.cuda else next_states
        terminated = terminated.cuda() if self.cuda else terminated
        truncated = truncated.cuda() if self.cuda else truncated

        targets = self.model(states)
        next_targets = self.target_model(next_states)
        targets[np.arange(self.batch_size), actions] = rewards + self.gamma * torch.amax(next_targets, axis=1) * (~terminated) * (~truncated)
        
        self.optimizer.zero_grad()
        loss = self.loss(self.model(states), targets)
        l = loss.item()
        loss.backward()
        self.optimizer.step()
        if self.epsilon > self.epsilon_min:
            self.epsilon *= self.epsilon_decay
        return l

    def preprocess(self, state):
        if self.name == 'MountainCar':
            return np.reshape(state, [1, self.observation_space])
        elif self.name == 'Pong':
            state = state[30:-10]/255.0
            if len(self.frames) < 4:
                self.frames = deque([state]*4, maxlen=4)
            self.frames.append(state)
            return np.stack(self.frames)[None, :, :, :]

    def train(self, episodes, checkpoint=10):
        rewards = []
        for e in tqdm(range(episodes)):
            self.frames = deque(maxlen=4)
            state, info = self.env.reset()
            state = self.preprocess(state)
            score, time_step, loss = 0, 0, []
            terminated = truncated = False
            while not terminated and not truncated:
                action = self.act(state)
                next_state, reward, terminated, truncated, info = self.env.step(action)
                next_state = self.preprocess(next_state)
                self.remember(state, action, reward, next_state, terminated, truncated, info)
                state = next_state
                score += reward
                time_step += 1
                l = self.replay()
                if l is not None:
                    loss.append(l)
            self.update_target_model()
            rewards.append(score)
            # write the reward and loss to a log file
            with open(f'./{self.name}/log.txt', 'a') as f:
                f.write(f'{e+1},{score},{np.mean(loss)},{time_step},{self.optimizer.param_groups[0]["lr"]}\n')
            if (e+1) % checkpoint == 0 or e == episodes - 1:
                self.save(f'./{self.name}/DQN_{e+1}.pth')
            self.scheduler.step(np.mean(loss))

        self.env.close()
        return rewards

    def test(self, episodes):
        rewards = []
        for e in range(episodes):
            state, info = self.env.reset()
            # state = np.reshape(state, [1, self.observation_space])
            self.frames = deque([state]*4, maxlen=4)
            state = self.preprocess(state)
            score = 0
            terminated = truncated = False
            while not terminated and not truncated:
                action = np.argmax(self.model(torch.Tensor(state)).detach().numpy())
                next_state, reward, terminated, truncated, info = self.env.step(action)
                next_state = self.preprocess(next_state)
                score += reward
                state = next_state
            rewards.append(score)
            print("episode: {}/{}, score: {}".format(e, episodes, score))
        self.env.close()
        return rewards

    def save(self, path = None):
        if path is None:
            path = f"./{self.name}/DQN.pth"
        torch.save(self.model.state_dict(), path)

    def load(self, path):
        self.model.load_state_dict(torch.load(path))

# create a Pong folder if it doesn't exist
import os

env = gym.make("MountainCar-v0")

agent = DQN(env, 'MountainCar', gamma=0.99, epsilon=1, epsilon_min=0.02, epsilon_decay=0.999, batch_size=32, lr=0.0001, cuda=True)


print('Training:')
rewards = agent.train(2000)
print('Training complete')

# save the model
agent.save('./Pong_2k.pth')
