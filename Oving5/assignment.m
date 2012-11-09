% Assignment 2 - Intensity transformation and filtering
% TDT4195 - Image Techniques
% ================================================
% Add code to this file where indicated and deliver on Itslearning before deadline


%!!!!!!!!!!!!!!FOR EACH CREATED/RESTORED IMAGE: SAVE IT AND UPLOAD ON ITSLEARNING!!!!!!!!!!


%%%%
%% Jeg har erstattet en del imshow med imwrite for mindre kludder og mer skriving til fil
%%%%


% === 1 - Intensity and Histogram processing ===

% Task 1.1 - Load the image dark.tif. Display the histogram on the screen. 
% Then use the imadjust function to make the image more visible, 
% show the new image and its histogram on screen


I = double(imread('dark.tif'));


I = imadjust(I, stretchlim(I), [0, 255], 0.8);

figure();
imhist(I);

%figure();
imwrite(I/255.0, 'dark_fixed.tif');


% Task 1.2 - Use the built-in Histogram Equalization function on the
% dark.tif image

I = double(imread('dark.tif'));
I = I/255.0;

I = histeq(I, 255);

%figure();
imwrite(I, 'dark_histeq.tif');


% Task 1.3 - Create a 4x4 image with random values from 0 to 7. Make a
% program that performs Histogram Equalization on this image. (do not use
% the built-in HE function) Tip: first create a histogram, then normalize it, 
% create cumulative distribution function and then do the intensity transformation.

image = ceil(rand(4,4)*8) - 1; % Creates a 4x4 random image with values 0 to 7
output = zeros(4,4); % the output image after HE
n = 4*4; % total size of image

c = zeros(8,1);

for i=1:8,
    c(i) = round(7*sum(sum(image<=i-1))/n);
end

for i=1:4,
    for j=1:4,
        output(i,j) = c(image(i,j)+1);
    end
end

imwrite(output, 'histeq.tif');


% Task 1.4 - Load the image mamm.tif and perform Histogram matching on this
% image with a gaussian with mean 0.5 and std 0.25. You can use the
% supplied gaussian function

I = double(imread('mamm.png'))/255.0;

g = gaussian(0.5, 0.25);

%I = histeq(I, g); %Burde virke, men funker ikke i Octave :(


% Task 1.5 - Load the image space.tif. Show the histogram and use HE to try
% to spread the intensity values. Look at both images. What happens? 
% Try to use Local adaptive Histogram Equalization instead and experiment 
% with the number of tiles to create the best result. Show the histogram 
% after local adaptive HE. What was best? Why?

I = double(imread('space.tif'))/255.0;
%I = histeq(I, 255);

%Fant noe som ser ut som skal fungere, men den finnes ikke i Octave.
%Prøvde mange forskjellige muligheter, men ingen ga det resultatet
%jeg ville.

%J = adapthisteq(I);

%figure(21);
%imshow(I);
%figure(22);
%imshow(J);

% === 2 - Spatial filtering ===

% Task 2.1 - Implement a filter with an averaging mask for images as a function 
% and make it possible to set the size of the filtering area (do not use the 
% built-in filtering functions) Tip: Use the matlab function sum() to 
% retrieve the sum of all values in an array

n = 15;

f = ones(n);
f = f;

I = rgb2gray(imread('assignment.png'));

J = filter2(f, I);
J = uint8(J/sum(f(:)));

imwrite(J, 'lenna_average.png');

% Task 2.2 - Implement the median filter for images as a function
% and make it possible to set the size of the filtering area (do not use the 
% built-in filtering/median functions). Tip: Use the matlab function 
% median() to retrieve the median value of an array

I = rgb2gray(imread('assignment.png'));

n = 15;

%Prøvde med på en versjon uten å bruke innebygd funksjon, men den var
%latterlig treg og virket ikke.... Har ikke tid til å prøve mer.
%Det er den her. Under gjør jeg det med octave-funksjoner.

%[h, w] = size(I);

%output = zeros(h, w);

%for i=1:h,
%    for j=1:w,
        %i_1 = max(i-1);
        %i1 = max(1, i-1);
        %i2 = min(h, i+1);
        %j1 = max(1, j-1);
        %j2 = min(w, j+1);
        %output(i, j) = median(I(i1:i2, j1:j2)(:));
%    end
%end

I = medfilt2(I, [n,n]);
%imshow(I);
imwrite(I, 'median.png')

% Task 2.3 - Create a gaussian mask with standard deviation = 1.0 and size 3x3

m = fspecial('gaussian', 3, 1.0);



% Task 2.4 - Load image assignment.png and convert it to grayscale and double 
% (values from 0.0 to 1.0)

I = double(rgb2gray(imread('assignment.png')))/255.0;


% Task 2.5 - Filter the image with the gaussian mask in task 3 and show the
% image on screen

J = filter2(m, I);

imwrite(J, 'gaussian.png');

%imshow(J);


% Task 2.6 - Create a copy of the image in task 4 with salt-and-pepper noise 
% and another copy of the image with gaussian noise. Show both images on
% screen

density = 0.2;
Isp = imnoise(I, 'salt & pepper');
Igaus = imnoise(I, 'gaussian');

imwrite(Isp, 'saltnpepper.png');
imwrite(Igaus, 'gaussian2.png');

%figure();
%imshow(Isp);
%figure();
%imshow(Igaus);


% Task 2.7 - For each noise type use an appropriate spatial filtering method to remove the noise 
% and experiment with different parameter values for the filtering methods

Isp = medfilt2(Isp, [3, 3]);
imwrite(Isp, 'saltnpepper_fixed.png')
%figure();
%imshow(Isp);

m = fspecial('gaussian', 3, 1.0);

Igaus = filter2(m, Igaus);
Igaus = medfilt2(Igaus, [3, 3]);
%figure();
imwrite(Igaus, 'gaussian_fixed.png');
%imshow(Igaus);


% Task 2.8 - Calculate the image gradients of assingment.png (task 2.4)

[DX, DY] = gradient(I);


% Task 2.9 - Show the vector field of the image gradients on top of the image 
% by using the quiver function after the following statement: 
% figure; imshow(<original image>), axis image; hold on; (zoom in to
% see all the vectors properly)

figure; imshow(I), axis image; hold on;
quiver(DX, DY);


% Task 2.10 - Calculate the magnitude of this vector field and display it

magn = sqrt(DX.*DX+DY.*DY);
imwrite(magn, 'magnitude_vector_field.png');
%imshow(magn);


% Task 2.11 - Blur assignment.png and then sharpen(improve the edges/remove
% blur) the blurred image. Show the images on screen

m = fspecial('gaussian', 5, 1.0);

I = filter2(m, I);


f = [0, 1, 0; 1, -4, 1; 0, 1, 0];
Ires = filter2(f, I);
I = I + 2*Ires;

imwrite(I, 'blured_and_sharpen_spatial.png')
%figure();
%imshow(I);

% === 3 - Frequency filtering ===

% Task 3.1 - Perform blurring and find edges of the same image as in task 
% 2.4 by filtering in the Frequency domain. You can use the
% lpfilter2 and hpfilter2 functions uploaded on itslearning

I = double(rgb2gray(imread('assignment.png')))/255.0;

[wx, hy] = size(I)

fftimg = fft2(I);
fftimg = fftshift(fftimg);

%Først blurer vi bildet
f = zeros(wx, hy);
n = 100;

f(wx/2-n/2:wx/2+n/2, hy/2-n/2:hy/2+n/2) = hpfilter2(n+1, n+1, 1);

fftimg = fftimg.*f;

%Så finner vi edger og plusser det på
f = ones(wx, hy);
n = 20;

f(wx/2-n/2:wx/2+n/2, hy/2-n/2:hy/2+n/2) = lpfilter2(n+1, n+1, 1);

edges = fftimg.*f;

fftimg = fftimg + edges;

fftimg = fftshift(fftimg);
image = abs(ifft2(fftimg));

imshow(image);

imwrite(image, 'blured_and_sharpen_frequency.png');






% Task 3.2 - (optional) Load the image clown.png convert it to double(0.0 to 1.0) and
% remove the periodic noise using a reject filter in the frequency domain.
% Tip: load the fourier spectrum in paint and remove the spikes manually and then
% inverse transform the filtered spectrum


