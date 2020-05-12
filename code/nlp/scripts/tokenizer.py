import spacy

class Tokenizer:
    def __init__(self, sentence, model='en_core_web_sm'):
        self.nlp = spacy.load(model)
        self.doc = self.nlp(sentence)

    def _print(self):
        print(f"Found {len(self.doc)} tokens in your sentence.\n")
        for token in self.doc:
            print(f"{token.pos_}\t-> {token.text}")


if __name__ == "__main__":
    string = '"The capital of Germany isn\'t Hamburg."'
    t = Tokenizer(string)
    t._print()

    