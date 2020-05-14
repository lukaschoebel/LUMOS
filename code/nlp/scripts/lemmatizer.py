import spacy

class Lemmatizer:
    def __init__(self, model='en_core_web_sm'):
        self.nlp = spacy.load(model)


if __name__ == "__main__":
    l = Lemmatizer()
    