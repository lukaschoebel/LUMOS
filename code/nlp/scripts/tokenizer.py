import spacy

class Tokenizer:
    def __init__(self, sentence, model='en_core_web_sm'):
        self.nlp = spacy.load(model)
        self.doc = self.nlp(sentence)

    def _print(self):
        print(f"Found {len(self.doc)} tokens in your sentence.\n")
        for token in self.doc:
            print(f"{token.pos_}\t-> {token.text}")

    def _print_ent(self):
        for entity in self.doc.ents:
            print(entity)
            print(entity.label_)
            print(str(spacy.explain(entity.label_)) + "\n")

    def _print_noun_chunks(self):
        for chunk in self.doc.noun_chunks:
            print(chunk)


if __name__ == "__main__":
    string = '"Siemens is building a factory in India for approximately 7.3 Million Euros."'
    t = Tokenizer(string)
    t._print_noun_chunks()

    