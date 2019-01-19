# def get_monthly_averages(lst):
#    data1 = 0
#    data2 = 0
#    index = 0
#    lindex1 = 0
#    lindex2 = 0
#    result = []
#    while lst[index][0] == lst[index + 1][0] and index != len(lst):
#        if index == len(lst) - 2:
#            data1 += float(lst[index + 1][1]) * int(lst[index + 1][2])
#            data2 += int(lst[index + 1][2])
#            avg = data1 / data2
#            result.append((lst[index - 1][0], avg))
#            return result
#        for p in lst[lindex1:index]:
#            data1 += float(p[1]) * int(p[2])
#        lindex1 = index
#
#        for q in lst[lindex2:index]:
#            data2 += int(q[2])
#        lindex2 = index
#        index += 1
#
#        if lst[index][0] != lst[index + 1][0]:
#            data1 += lst[index][1] * lst[index][2]
#            data2 += lst[index][2]
#            avg = data1 / data2
#            result.append((lst[index - 1][0], avg))
#            lindex1 = index
#            lindex2 = index
#            index += 1
#            data1 = 0
#            data2 = 0
#            avg = 0
#
#
# def print_info(dic):
#    best = 0
#    bestkey = 0
#    best6 = []
#
#    cnt = 0
#    while cnt != 6:
#        cnt += 1
#        for key1 in dic:
#            if dic[key1] > best:
#                best = dic[key1]
#                bestkey = key1
#        best6.append((bestkey, best))
#        dic.pop(bestkey)
#        best = 0
#        bestkey = 0
#    print('Best:')
#    for bst in best6:
#        print(bst, end='\n')
#
#    worst = 99999999999999
#    worstkey = 0
#    worst6 = []
#    cnt = 0
#    while cnt != 6:
#        cnt += 1
#        for key2 in dic:
#            if dic[key2] < worst:
#                worst = dic[key2]
#                worstkey = key2
#        worst6.append((worstkey, worst))
#        dic.pop(worstkey)
#        worst = 99999999999999
#        worstkey = 0
#    print('Worst:')
#    for wst in worst6:
#        print(wst, end='\n')
#
#
# with open(str(input("Enter the name of the file:")) + '.csv', 'r') as f:
#    arr = []
#    for i in f:
#        w = i.strip('\n').split(',')
#        arr.append((w[0], w[1:]))
#    del arr[0]
# date = []
# close = []
# volume = []
#
# for i in arr:
#    i = list(i)
#    date.append(i[0].split('-'))
# for i in date:
#    del (i[2])
# for i in arr:
#    close.append(i[1][4])
#    volume.append(i[1][5])
# new_arr = []
# for a, b, c in zip(date, close, volume):
#    new_arr.append((a, float(b), int(c)))
#
# monthly_averages = get_monthly_averages(new_arr)
#
# dictionary = {}
# for item in monthly_averages:
#    dictionary.setdefault(str(item[0][0]) + '-' + str(item[0][1]), item[1])
#
# print_info(dictionary)

def get_monthly_averages(lst):
    data1 = 0
    data2 = 0
    index = 0
    lindex1 = 0
    lindex2 = 0
    result = []
    while lst[index][0] == lst[index + 1][0] and index != len(lst):
        if index == len(lst) - 2:
            data1 += float(lst[index + 1][1]) * int(lst[index + 1][2])
            data2 += int(lst[index + 1][2])
            avg = data1 / data2
            result.append((lst[index - 1][0], avg))
            return result
        for p in lst[lindex1:index]:
            data1 += float(p[1]) * int(p[2])
        lindex1 = index

        for q in lst[lindex2:index]:
            data2 += int(q[2])
        lindex2 = index
        index += 1

        if lst[index][0] != lst[index + 1][0]:
            data1 += lst[index][1] * lst[index][2]
            data2 += lst[index][2]
            avg = data1 / data2
            result.append((lst[index - 1][0], avg))
            lindex1 = index
            lindex2 = index
            index += 1
            data1 = 0
            data2 = 0
            avg = 0
    else:
        index += 1
        while lst[index][0] == lst[index + 1][0] and index != len(lst):
            if index == len(lst) - 2:
                data1 += float(lst[index + 1][1]) * int(lst[index + 1][2])
                data2 += int(lst[index + 1][2])
                avg = data1 / data2
                result.append((lst[index - 1][0], avg))
                return result
            for p in lst[lindex1:index]:
                data1 += float(p[1]) * int(p[2])
            lindex1 = index

            for q in lst[lindex2:index]:
                data2 += int(q[2])
            lindex2 = index
            index += 1

            if lst[index][0] != lst[index + 1][0]:
                data1 += lst[index][1] * lst[index][2]
                data2 += lst[index][2]
                avg = data1 / data2
                result.append((lst[index - 1][0], avg))
                lindex1 = index
                lindex2 = index
                index += 1
                data1 = 0
                data2 = 0
                avg = 0


def print_info(LOT):
    best = ('', 0.0)
    best6 = []

    cnt = 0
    while cnt != 6:
        cnt += 1
        for T in LOT:
            if T[1] > best[1]:
                best = T
        best6.append(best)
        LOT.remove(best)
        best = ('', 0.0)
    print('Best:')
    for bst in best6:
        print(bst, end='\n')

    worst = ('', 999999999.99)
    worst6 = []
    cnt = 0
    while cnt != 6:
        cnt += 1
        for T in LOT:
            if T[1] < worst[1]:
                worst = T
        worst6.append(worst)
        LOT.remove(worst)
        worst = ('', 999999999.99)
    print('Worst:')
    for wst in worst6:
        print(wst, end='\n')


with open(str(input("Enter the name of the file:")) + '.csv', 'r') as f:
    arr = []
    for i in f:
        w = i.strip('\n').split(',')
        arr.append((w[0], w[1:]))
    del arr[0]
date = []
close = []
volume = []

for i in arr:
    i = list(i)
    date.append(i[0].split('-'))
for i in date:
    del (i[2])
for i in arr:
    close.append(i[1][4])
    volume.append(i[1][5])
new_arr = []
for a, b, c in zip(date, close, volume):
    new_arr.append((a, float(b), int(c)))

monthly_averages = get_monthly_averages(new_arr)

print_info(monthly_averages)