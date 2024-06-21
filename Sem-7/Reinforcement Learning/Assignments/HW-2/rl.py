import numpy as np
import gymnasium as gym

def policy_evaluation(policy: np.array, env: gym.Env, gamma: float = 1.0, delta_min: float = 1e-9) -> np.array:
	# Initialize the value function
	V = np.zeros(env.nS)
	# Iterative application of Bellman Evaluation Equation
	while True:
		delta = 0
		# For each state, perform a "full backup"
		for s in range(env.nS):
			v_s = 0
			# Look at the possible next actions
			for a, action_prob in enumerate(policy[s]):
				# For each action, look at the possible next states...
				for  prob, next_state, reward, done in env.P[s][a]:
					# Calculate the expected value
					v_s += action_prob * prob * (reward + gamma * V[next_state])
			# How much our value function changed (across any states)
			delta = max(delta, np.abs(v_s - V[s]))
			V[s] = v_s
		# Stop evaluating once our value function change is below a threshold
		if delta < delta_min:
			break
	return np.array(V)