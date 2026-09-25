import struct

path = "solnascente-3d/data/prestack/metadata"

# Binary layout: 40 bytes total
# dt (double)     -> 8 bytes
# delrt (double)  -> 8 bytes
# ns (uint)       -> 4 bytes
# fintil (uint)   -> 4 bytes
# dx (double)     -> 8 bytes
# dy (double)     -> 8 bytes
fmt = "<d d I I d d"  # equivalent to '<ddIIdd'

with open(path, "rb") as f:
    data = f.read(struct.calcsize(fmt))

if len(data) != struct.calcsize(fmt):
    raise ValueError(f"Expected {struct.calcsize(fmt)} bytes, got {len(data)} bytes")

values = struct.unpack(fmt, data)
dt, delrt, ns, fintil, dx, dy = values

print(f"dt     = {dt}")
print(f"delrt  = {delrt}")
print(f"ns     = {ns}")
print(f"fintil = {fintil}")
print(f"dx     = {dx}")
print(f"dy     = {dy}")

