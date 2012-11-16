% Load image
I = im2double(imread('../shapes/shape1.png'));
% Remove noise
I = medfilt2(I, [3,3], 'ones');

% Retrieve objects in image (hint: bwlabel)
I = not(logical(I));

%[L, num] = bwlabel(I);

[B,L] = bwboundaries(I, 8, 'noholes');


% Initialize the result data structure
data(1).center = [0.0 0.0]; % centroid
data(1).attributes = [0]; % radius or corner positions
% a circle will only have one attribute (The radius) 
% the triangle should have 3 corners with x and y coordinates
% the square should have 4 corners with x and y coordinates
% Example for a triangle:
% data(i).attributes = [0.7578, 0.8203; 0.8906, 0.6367; 0.6758, 0.6094];

% For each object
I2 = L/10;
[height width] = size(I);
for k = 1:length(B),
    k;

    % Find contour (hint: bwboundaries)
    b = B{k};
    
    % Calculate centroid (hint: centroid = average position of each pixel 
    % on the contour)
    cy = round(sum(b(:,1))/length(b));
    cx = round(sum(b(:,2))/length(b));
    data(k).center = [cy cx]/height;

    I2(cy,cx) = 1.0;

    % Find corners (if any) (hint: look at the contour signature which is
    % the length from the centroid)

    [phi, r] = cart2pol(b(:,2)-cx, b(:,1)-cy);
    %figure();
    
    [max_r, max_index] = max(r);
    my = b(max_index,1);
    mx = b(max_index,2);
    %I2(my, mx) = 1.0;

    m = [1,2,3,2,1];
    m = m/sum(m);
    %r = filter(m,1, r);

    %figure();
    %plot(phi, r, '.');



    max_r = max(r);
    min_r = min(r);
    if !(max_r/min_r < sqrt(2))
        diff = max_r-min_r;

        corner_indexes = find(r>max_r-max_r*0.10==1);
        corner_indexes;

        if corner_indexes(length(corner_indexes)) == length(b)
            last = 0;
        else
            last = -200;
        end
        indexes = [];
        found = [];
        for i = 1:length(corner_indexes)
            index = corner_indexes(i);
            if (!(last == index-1)) || last == -200
                indexes = [indexes ; index];
            end
            %if last == index-1 || last == -200
            %    found = [found ; index];
            %else
            %    if length(found) > 0
            %        indexes = [indexes ; floor(median(found))];
            %    end
            %    found = [index];
            %end
            last = index;
        end
        corners = b(indexes,:);
        %if length(found) > 0    
        %    indexes = [indexes ; floor(median(found))];
        %    indexes;
        %    
        %else
        %    corners = [];
        %end

        [h w] = size(corners);
        for i = 1:h
            y = corners(i, 1);
            x = corners(i, 2);
            I2(y,x) = 1;
        end

        
        
        
        for i = 1:length(b),
            y = b(i, 1);
            x = b(i, 2);
            len = sqrt(x^2 + y^2);
        end

        data(k).attributes = corners/height;
    else
        % If no corners, assume shape is a circle and store radius instead
        radius = sum(r)/length(r);
        data(k).attributes = [radius]/height;
    end
    
    
    
    % Store result in the data list
end
% End for each object

writeAttributesToFile('result.txt', data);

I2 = uint8(I2*255);

imwrite(I2, 'result.bmp');
