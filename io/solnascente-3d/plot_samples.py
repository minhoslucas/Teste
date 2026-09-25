import numpy as np
import matplotlib.pyplot as plt
import sys

def get_param(array, base, size, ns, np):
    return [[array[x] for x in range(base+y*ns*np,(y+1)*ns*np,np)] for y in range(0,size)]

with open("samples", "rb") as f:
    array = np.fromfile(f, dtype=np.float32)

ns = int(sys.argv[1])
num_results = int(sys.argv[2])

to_clip = False
if (len(sys.argv) > 3):
    clip = float(sys.argv[3])
    to_clip = True

colormap="binary"
#if (len(sys.argv) > 3):
#    colormap=sys.argv[3]

size = int(array.size / ns / num_results)

for i in range(0, num_results):
    plt.figure()
    if (i == 0 or i==5):
        colormap="jet"
    else:
        colormap="seismic"
    param = np.array(get_param(array, i, size, ns, num_results)).astype(np.float32).transpose()
    if (to_clip):
        plt.imshow(param.clip(-clip, clip), aspect="auto", cmap=colormap)
    else:
        plt.imshow(param, aspect="auto", cmap=colormap)
    plt.colorbar()
    plt.savefig("figure_{}.png".format(i))
plt.show()
plt.close()
