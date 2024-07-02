# Rumor Verification using Evidence from Authorities

The project was done as a part of the course CS5803: Natural Language Processing, Spring 2024 at IIT Hyderabad under the guidance of [Prof. Maunendra Sankar](https://www.iith.ac.in/cse/maunendra/).

## Abstract
The spread of rumors on social media platforms like Twitter can have significant real-world consequences. This work
addresses the critical task of rumor verification.

To solve this problem, we design a two-stage pipeline. In the first stage, we finetune and use ColBERT for information retrieval to fetch the top-k similar tweets for a given rumor. In the second stage, we use MISTRAL to appropriately classify the rumor and retrieve the top-5 evidences using the tweets retrieved.

## Report
The detailed report outlining the problem statement, methodology, and results can be found in [Report.pdf](Report.pdf).

## Code
The designed pipeline is implemented in [nlp-project.ipynb](nlp-project.ipynb). The code can be run on Google Colab or Jupyter Notebook.

## Team Members
* [Taha Adeel Mohammed](https://github.com/Taha-Adeel)
* [Srikaran Perambuduri](https://github.com/Srikaran-p)
* [Shambu Kavir](https://github.com/Shambu-K)

## License
Distributed under the MIT License.