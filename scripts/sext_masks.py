for n in range(32):
    mask = 0
    for i in range(n, 32):
        mask |= 1 << i
    print(hex(mask))
