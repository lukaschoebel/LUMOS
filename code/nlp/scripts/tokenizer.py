import spacy

class Tokenizer:
    def __init__(self, sentence, model='en_core_web_sm'):
        self.nlp = spacy.load(model)
        self.doc = self.nlp(sentence)

    def _print(self):
        for token in self.doc:
            print(f"{token.text} - {token.pos_}")


if __name__ == "__main__":
    string = '"The capital of Germany isn\'t Hamburg."'
    t = Tokenizer(string)
    t._print()

    