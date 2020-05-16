import os
import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.decomposition import NMF

class Factorizer:
    def __init__(self, path, classes=7):
        self.data = pd.read_csv(path)
        self.tfidf = TfidfVectorizer(max_df=0.9, min_df=2, stop_words='english')

        self.dtm = self.tfidf.fit_transform(self.data['Article'])

        self.nmf = NMF(n_components=classes, random_state=77)
        self.nmf.fit(self.dtm)

    def get_topk(self, top_k=10):
        """ Prints all topics and their top_k words and returns data object

        Arguments:
            top_k {int} -- Specifies how many top k words should be included

        Returns:
            Data Frame -- data with assigned topic appended in new column
        """

        for i, t in enumerate(self.nmf.components_):
            print(f"Topic #{i}")
            print([self.tfidf.get_feature_names()[idx] for idx in t.argsort()[-top_k:]])
            print('\n')

        # return data object with assigned topic in new column
        self.data['Topic'] = self.nmf.transform(self.dtm).argmax(axis=1)
        return self.data



if __name__ == "__main__":
    f = Factorizer(os.getcwd().replace('/scripts', '/data/articles.csv'))
    data = f.get_topk(top_k=15)
    print(data)