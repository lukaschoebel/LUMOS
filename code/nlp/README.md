# NLP Experiments

## Objective

This folder contains experiments that aim to provide basic understanding of Natural Language Processing and explores the usage of important tools as e.g. `spaCy` and `Keras`.

## Good To Know

- `NLTK` older than `spaCy`, but better for sentiment analysis
- **Tokenization** (spacy):
  - `Prefix` (chars @ beginning): `$`
  - `Suffix` (chars @ end): `!`
  - `Infix` (chars in between): `-`
  - `Exception` (special rule): `hello world.`

## Get Started

```bash
pip install -U -r requirements.txt

# spacy models
python -m spacy download en_core_web_sm
```
