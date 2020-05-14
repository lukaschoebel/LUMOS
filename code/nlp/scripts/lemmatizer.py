import spacy

class Lemmatizer:
    def __init__(self, model='en_core_web_sm'):
        self.nlp = spacy.load(model)

    def _print_lemmas(self, sentence: str):
        text = self.nlp(sentence)

        for token in text:
            print(f"{token.text:{12}} {token.pos_:{6}} {token.lemma:<{20}} {token.lemma_}")


if __name__ == "__main__":
    sentence = 'I am a student studying various Natural Language Processing algorothms to obtain a deeper understanding.'
    l = Lemmatizer()
    l._print_lemmas(sentence)



