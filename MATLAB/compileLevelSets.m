%%
allFileNames = 'makeSignedDistanceField.cpp';

sourceFiles =dir('../src');
files = sourceFiles(~[sourceFiles.isdir]);
for file = {files.name}      
    if strcmp(file{1}(end - 1:end), '.c') || strcmp(file{1}(end - 3:end), '.cpp') && ~strcmp(file{1}, 'makeSignedDistanceField.cpp')
        allFileNames = [allFileNames ' ../src/' file{1}];
    end
end
allFileNames = [allFileNames, ' '];

%%
libraries = '-L"../lib" -llapack -lblas ';
% libraries = '-L"/usr/lib64/" -llapack.so.3 -lblas.so.3 ';
options = '-I../include';

eval(['mex ' allFileNames, libraries, options]);

%%

objFile = 'TestFiles/monkey.obj';
sdfFile = 'TestFiles/monkey.sdf.nii';
x = 32;
y = 32;
z = 32;
dimensions = [x, y, z];
writeMatrix = eye(4);
transformationMatrix = eye(4);
% transformationMatrix(1, 4) = 1;
% transformationMatrix(2, 4) = 1;
% transformationMatrix(3, 4) = 1;

makeSignedDistanceField(objFile, sdfFile, dimensions, writeMatrix, transformationMatrix);
 
%%
objFile = 'TestFiles/cube.obj';
sdfFile = 'TestFiles/cube.sdf.nii';
x = 3;
y = 3;
z = 3;
dimensions = [x, y, z];
writeMatrix = eye(4);
transformationMatrix = eye(4);

makeSignedDistanceField(objFile, sdfFile, dimensions, writeMatrix, transformationMatrix);
 












