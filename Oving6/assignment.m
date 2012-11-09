% Assignment 3 - Segmentation and morphological operations
% TDT4195 - Image Techniques
% ================================================
% Add code to this file where indicated and deliver on Itslearning before deadline

%!!!!!!!!!!!!!!FOR EACH CREATED/RESTORED IMAGE: SAVE IT AND UPLOAD ON ITSLEARNING!!!!!!!!!!

% === 1 - Morphological operations ===

% Task 1.1 - Load the image bone.png and find its skeleton using
% thinning

% Task 1.2 - Perform dilation on the skeleton with a disk

% Task 1.3 - Perform erosion on the dilated skeleton with a smaller disk

% Task 1.4 - Perform closing on the image a.png with a large square

% === 2 - Thresholding ===

% Task 2.1 - Load the threshold.png image, look at its histogram and perform
% thresholding with an appropriate treshold. Display threshold

I = imread('threshold.png');
I = double(I>40);
imwrite(I, 'threshold_done.png');

% Task 2.2 - Implement a function that does basic global optimal thresholding 
% Execute function on threshold.png and display the result. (Do not use graytresh)

% === 3 - Edge detection ===

% Task 3.1 - Load the image edgess and use sobel mask to find the edges
% of the image. Display the result

% Task 3.2 - Use the canny edge detector on the edges.png image. Display
% result.

% Task 3.3 - Compute the Hough transform of the result from task 3.1. Display
% the Hough transform on the screen.

% Task 3.4 - Find the 3 most clear lines using the Hough transform from the 
% previous task and display them on top of the original image

% === 4 - Region Growing ===

% Task 4.1 - Implement a region growing function that takes an image, a
% set of seed points and a threshold as input. The treshold defines the
% maximum difference in intensity between the seed and the candidate pixel 
% the region growing should allow.

% Task 4.2 - Perform region growing on the image region.png to segment the 
% bright sparks in the image. Display the result

% === 5 - Watershed ===

% Load the image watershed.png and perform watershed segmentation on the
% gradient information of the image

% === 6 - Skittle segmentation ===
% Load the image skittles2.jpg and make a system that counts the number of
% green skittles.

% Tips: normalize the colors (that is normalize the color vectors), 
% do a color threshold segmentation and 
% check out the functions imfill, bwconncomp and labelmatrix
