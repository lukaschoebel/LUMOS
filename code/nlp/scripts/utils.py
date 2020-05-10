import os
import slate3k as slate

def clean(s: str):
    """Removes unnecessary characters from a given string.

    Arguments:
        s {str} -- String that should be cleaned
    
    Returns:
        s {str} -- Cleaned string
    """

    s = s.replace('\n', '')

    return s

def load(path: str):
    """Loads a file

    Arguments:
        path {str} -- Path to a .txt file

    Returns:
        List -- Returns a list of lines
    """

    f = open(path, 'r')
    data = []

    for line in f:
        data.append(clean(line))
    f.close()

    return data

def loadPDF(path: str):
    """Loads a given .pdf file

    Arguments:
        path {str} -- Path to .pdf file

    Returns:
        List -- List of pages as strings 
    """

    with open(path, 'rb') as f:
        extracted_text = slate.PDF(f)
    
    return extracted_text
    

if __name__ == "__main__":
    os.chdir(f"{os.getcwd()}/scripts")
    # data = load('../data/iphone07.txt')
    # print(data[:1])

    loadPDF('../data/iphone07.pdf')
