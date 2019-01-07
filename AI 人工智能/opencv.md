1、升级GCC 到 8.1
2、
http://rpmfind.net/linux/fedora/linux/development/rawhide/Everything/x86_64/os/Packages/o/opencv-contrib-3.4.1-3.fc29.i686.rpm

# grayscale
```python
img = cv2.imread('./src/px/4-gb-wr.bmp', cv2.IMREAD_GRAYSCALE)
cv2.imwrite('./dst/px-4-gb-wr--grayscale.png', img)
```

```
sh$ vi ./src/px/4-gb-wr.bmp
|[
    00000000: 424d 2c00 0000 0000 0000 1a00 0000 0c00  BM,.............
    00000010: 0000 0200 0200 0100 1800 ffff ff00 00ff  ................
    00000020: 0000 00ff 00ff 0000 0000 0000 0a         .............
]|


```