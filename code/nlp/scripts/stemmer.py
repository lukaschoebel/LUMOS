import nltk
from nltk.stem.porter import PorterStemmer
from nltk.stem.snowball import SnowballStemmer

class Stemmer:
    def __init__(self, words: list, stemmer='sb'):
        self.words = words
        self.s = PorterStemmer() if stemmer == 'ps' else SnowballStemmer(language='english')

    def _print_reduced(self):
        for word in self.words:
            print(word + " to " + self.s.stem(word))


if __name__ == "__main__":
    words = ['singer', 'sang', 'sung', 'sings']

    s = Stemmer(words)
    s._print_reduced()
