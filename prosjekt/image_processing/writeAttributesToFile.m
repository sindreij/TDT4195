function [ ] = writeAttributesToFile(filename, data )
    
    file = fopen(filename, 'w');
    
    formatCircle = '%4.3f %4.3f %4.3f\n';
    formatTriangle = '%4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f\n';
    formatSquare = '%4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f %4.3f\n';
    n = size(data);
    for i = 1:n(2)
        attr = data(i).attributes;
        s = size(attr);
        attr = attr';
        if s(1) == 1
            % Circle
            fprintf(file, formatCircle, [data(i).center attr(:)']);
        elseif s(1) == 3
            % Triangle
            fprintf(file, formatTriangle, [data(i).center attr(:)']);
        elseif s(1) == 4
            % Square
            fprintf(file, formatSquare, [data(i).center attr(:)']);
        end
    end
    
    fclose(file);
end

