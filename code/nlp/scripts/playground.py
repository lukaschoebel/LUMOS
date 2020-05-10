import os

def load(path: str):
    f = open(path, 'r')
    data = []

    for line in f:
        data.append(line)
    f.close()

    return data


if __name__ == "__main__":
    os.chdir(f"{os.getcwd()}/scripts")
    data = load('../data/iphone07.txt')
    print(data[:1])
