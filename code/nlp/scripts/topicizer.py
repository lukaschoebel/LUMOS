import os
import pandas as pd
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.decomposition import LatentDirichletAllocation

class Topicizer:
    def __init__(self, path):
        self.data = pd.read_csv(path)
        self.cv = CountVectorizer(max_df=0.9, min_df=2, stop_words='english')
        # vocabulary as list with: cv.get_feature_names()

        # fit LDA to vectorized words
        self.dtm = self.cv.fit_transform(self.data['Article'])
        LDA = LatentDirichletAllocation(n_components=7, random_state=42)
        self.LDA = LDA.fit(self.dtm)
    
    def get_topk(self, top_k=10):
        """ Prints all topics and their top_k words and returns data object

        Arguments:
            top_k {int} -- Specifies how many top k words should be included

        Returns:
            Data Object -- data with assigned topic appended in new column
        """

        for i, t in enumerate(self.LDA.components_):
            print(f"Topic #{i}")
            print([self.cv.get_feature_names()[idx] for idx in t.argsort()[-top_k:]])
            print(f"\n")

        # return data object with assigned topic in new column
        self.data['Topic'] = self.LDA.transform(self.dtm).argmax(axis=1)
        return self.data


if __name__ == "__main__":
    t = Topicizer(os.getcwd().replace('/scripts', '/data/articles.csv'))
    data = t.get_topk(top_k=15)
    print(data)