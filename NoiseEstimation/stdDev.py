import cv2

import numpy as np
import sys

img = cv2.imread(sys.argv[1], 0)
h, w = img.shape

# img = np.float32(img)

# kernel = np.array([[1, -2, 1], [-2, 4, -2], [1, -2, 1]], dtype=np.float32)
# dst = cv2.filter2D(img, -1, kernel)

dst = cv2.Laplacian(img, cv2.CV_64F)

# Absolute sum of laplacian
sigma = np.sum(np.abs(dst))

# Rescaling sigma with appropriate coefficients
sigma = sigma*np.sqrt(0.5*np.pi)/((6.0*(w-2)*(h-2)))

print "Std dev = " + str(sigma)

cv2.imshow("dst", dst);cv2.waitKey(0);
