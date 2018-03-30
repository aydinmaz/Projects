
# Python 2/3 compatibility
from __future__ import print_function

import numpy as np
import cv2


def inside(r, q):
    rx, ry, rw, rh = r
    qx, qy, qw, qh = q
    return rx > qx and ry > qy and rx + rw < qx + qw and ry + rh < qy + qh


def draw_detections(img, rects, thickness = 1):
    for x, y, w, h in rects:
        # the HOG detector returns slightly larger rectangles than the real objects.
        # so we slightly shrink the rectangles to get a nicer output.
        pad_w, pad_h = int(0.15*w), int(0.05*h)
        cv2.rectangle(img, (x+pad_w, y+pad_h), (x+w-pad_w, y+h-pad_h), (0, 255, 0), thickness)


if __name__ == '__main__':
    import sys
    from glob import glob
    import itertools as it

    hog = cv2.HOGDescriptor()
    hog.setSVMDetector( cv2.HOGDescriptor_getDefaultPeopleDetector() )

    cap = cv2.VideoCapture("test3.mp4")

    while True:

        _, frame = cap.read()

        frame = cv2.resize(frame, None, fx=.5,fy=.5)
        found, w = hog.detectMultiScale(frame, winStride=(4,4), padding=(8,8), scale=1.05)
        found_filtered = []
        for ri, r in enumerate(found):
            for qi, q in enumerate(found):
                if ri != qi and inside(r, q):
                    break
            else:
                found_filtered.append(r)
        draw_detections(frame, found)
        draw_detections(frame, found_filtered, 3)
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(frame, '%d person found ' % (len(found_filtered)), (20, 50), font, 0.8, (255, 0, 255), 2, cv2.LINE_AA)
        print('%d  found' % (len(found_filtered)))
        cv2.imshow('img', frame)
        ch = cv2.waitKey(1)
        if ch == 27:
            break
    cv2.destroyAllWindows()