from hashlib import md5
import os
import sys

Ignore = ('Thumbs.db',)

def getmd5(filename):
    return md5(open(filename, 'rb').read(-1)).hexdigest()

def usage():
    print ('Usage: remove-duplicates.py DIRECTORY')
    sys.exit(1)

def main(argv):
    if len(argv) < 1: usage()
    
    DIR = os.path.abspath(argv[0])
    print ('Reading sizes...')
    # Create a dictionary keyed by size, with each entry holding a list of
    # filenames of that size.
    data = {}
    for root, dirs, files in os.walk(DIR):
        for name in files:
            if name in Ignore: continue
            path = os.path.join(root, name)
            size = os.path.getsize(path)
            if not data.get(size):
                data[size] = []
            data[size].append(path)
    # For each key, checksum each list entry and compare.
    removed = 0
    for k in data.keys():
        dk = data[k]
        if len(dk) > 1:
            #print k, len(dk)
            s = {}
            for j in dk:
                SUM = getmd5(j)
                if s.get(SUM):
                    print (j, 'is a duplicate of', s[SUM])
                    try:
                        os.remove(j)
                        removed += 1
                    except:
                        pass
                else:
                    s[SUM] = j
    print ('Done, {} files removed.'.format(removed))

if __name__ == '__main__':
    main(sys.argv[1:])
