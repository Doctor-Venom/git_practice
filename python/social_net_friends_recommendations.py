import numpy as np


def open_file():
    while True:
        file_name = input("Enter the file name to read data:")
        try:
            fp = open(file_name, 'r')
            return fp
        except:
            print('The file with the specified name could not be opened or does not exist.')


def read_file(fp):
    data = fp.readlines()
    network = []
    for i in data[1:]:
        network.append(tuple(map(int, i.strip('\n').split())))
    return int(data[0]), network


def calc_recommendations(network):  # O(n^2)...
    users_friends = [set() for _ in range(max(max(network, key=lambda x: x[0])[0], max(network, key=lambda x: x[1])[1]) + 1)]
    net_users = set()
    for i in network:
        users_friends[i[0]].add(i[1])
        users_friends[i[1]].add(i[0])
        net_users.add(i[0])
        net_users.add(i[1])
    users_notfriends = [0] * (max(net_users) + 1)
    for i in net_users:
        users_notfriends[i] = set(x for x in net_users if x not in users_friends[i] and x != i)

    def calc_common_friends(a, b):
        temp = [x for x in a if x in b]
        return len(temp)

    common_friends_matrix = [[0 for _ in range(max(net_users) + 1)] for _ in range(max(net_users) + 1)]
    for i in net_users:
        for j in users_notfriends[i]:
            if i != j:
                common_friends_matrix[i][j] = calc_common_friends(users_friends[i], users_friends[j])
    recommendations = [0] * (max(net_users) + 1)
    for i in net_users:
        recommendations[i] = np.argmax(common_friends_matrix[i])
    return recommendations


def recommend(recommendations):
    print("[!] Type break to stop.")
    while True:
        try:
            ID = input("Enter User ID to Get Recommendations: ")
            if  ID.lower() == 'break':
                print("[!] Terminating")
                break
            print("[+] recommended friend for user ID (" + str(ID) + ") is: " + str(recommendations[int(ID)]))
        except:
            print("[-] User ID Does not exist.")
            continue


def main():
    numof_users, network = read_file(open_file())
    recommend(calc_recommendations(network))


if __name__ == "__main__":
    main()
