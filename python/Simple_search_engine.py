from string import *
import os, sys, threading, tkinter as tk


def read():
    d = open('docs.txt').read().split('<NEW DOCUMENT>')
    idx = 0
    global docs
    docs = {}
    for i in d:
        docs[idx] = i
        idx += 1


def search(keywords):
    keywords = keywords.split()
    results = []
    for k, v in docs.items():
        if all(i.lower() in v.lower() and
               v.lower()[v.lower().index(i.lower()): v.lower().index(i.lower()) + len(i) + 1][
                   -1] in punctuation + whitespace for i in keywords):
            results.append(k)
    d = {i: '' for i in results}
    for i in results:
        for j in keywords:
            x = docs[i].lower().index(j.lower())
            capture = docs[i][x:x + 30].replace('\n', ' ')
            d[i] += f'{capture}.... '
    if len(d):
        for i in d.items():
            txt.insert(tk.END, f'[Capture from book {i[0]}]: {i[1]}\n')
    if len(results):
        results = ' '.join([str(i) for i in results])
        txt.insert(tk.END, f'\n\nDocuments fitting search:[{results}]\n\n')
        txt.see(tk.END)
    else:
        txt.insert(tk.END, 'No relevant documents were found.')
        txt.see(tk.END)


def display(book_index):
    book_index = int(book_index)
    if docs.get(book_index, 0):
        txt.insert(tk.END, docs[book_index])
        txt.insert(tk.END, '=' * 70)
        txt.see(tk.END)
    else:
        txt.insert(tk.END, "Can't find a book with the specified index.")
        txt.see(tk.END)


def main():
    read()
    root = tk.Tk()

    ########
    def SEARCH():
        query = [search_entry.get()]
        thread = threading.Thread(target=search, args=query)
        thread.start()

    def DISPLAY():
        query = [display_entry.get()]
        thread = threading.Thread(target=display, args=query)
        thread.start()

    tk.Button(root, text="  Search docs  ", command=SEARCH).grid(row=0, column=0)
    search_entry = tk.Entry(root)
    search_entry.grid(row=0, column=1, sticky='W')
    tk.Button(root, text='View document', command=DISPLAY).grid(row=1, column=0)
    display_entry = tk.Entry(root)
    display_entry.grid(row=1, column=1, sticky='W')
    global txt
    txt = tk.Text(root)
    txt.grid(row=2, column=1, rowspan=3, columnspan=2)
    tk.Button(root, text="Quit", fg="red", command=quit).grid(row=2, column=0, sticky='N')
    ########

    root.mainloop()


if __name__ == '__main__':
    main()
