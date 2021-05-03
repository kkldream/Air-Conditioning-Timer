header = [9000, 4450]
one = [550, 1700]
zero = [550, 550]

def str2arr(str):
    arr = str.split(' ')
    for i in range(len(arr)):
        arr[i] = int(arr[i])
    return arr

def arr2hex(arr):
    var = 0
    for i in range(len(arr)):
        if i < 2 or arr[i] > 0: continue
        if arr[i] < -800:
            var += 1 << 103 - int((i - 1) / 2 - 1)
    return var

def printArr(arr):
    print('{', end='')
    for i in range(len(arr)):
        if i % 10 == 0 and i != 0: print()
        if i == len(arr) - 1: print(abs(arr[i]), end='')
        else: print(abs(arr[i]), end=', ')
    print('}')
    print(f'Num = {len(arr)}')

key_str = '9007 -4476 538 -1709 521 -1709 537 -581 523 -606 498 -606 510 -569 535 -1733 513 -1709 525 -1709 537 -1709 525 -1709 537 -593 511 -1745 488 -606 510 -606 498 -1745 501 -593 511 -605 499 -581 535 -593 511 -569 535 -1709 537 -1709 525 -1709 537 -605 499 -581 523 -581 523 -606 510 -582 522 -606 498 -606 510 -606 499 -606 498 -582 522 -582 535 -594 510 -581 523 -1709 537 -606 498 -1709 537 -569 535 -582 522 -606 510 -570 534 -570 534 -582 522 -582 535 -569 535 -606 498 -581 523 -582 534 -606 498 -606 498 -1709 538 -581 523 -581 535 -570 534 -606 498 -582 522 -606 510 -570 534 -606 498 -643 474 -630 474 -581 523 -581 535 -569 535 -570 534 -582 522 -606 510 -570 534 -582 522 -582 523 -581 535 -642 462 -582 534 -602 498 -1710 561 -545 534 -582 522 -606 511 -569 535 -606 498 -581 535 -569 535 -606 498 -582 522 -582 534 -1710 524 -606 510 -1710 524 -582 534 -594 510 -606 498 -606 498 -582 544 -1697 537 -1709 525 -1709 537 -1709 525 -1709 537 -606 498 -606 498 -581 535'
key_arr = str2arr(key_str)
key_hex = arr2hex(key_arr)
print(f'{key_hex:x}')
printArr(key_arr)
