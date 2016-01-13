%%
sourceDirectory = '../src';
allFileNames = 'makeSignedDistanceField.cpp';
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'Matrix.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'Matrix44.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'SignedDistanceField.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'SignedDistanceFieldFactory.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'Volume.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'Volume4D.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'LevelSet/makelevelset3.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'NifTI/nifti1_io.c')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'NifTI/znzlib.c')];
allFileNames = [allFileNames , ' '];


%%
libraries = '-L"../lib" -llapack -lblas ';
% libraries = '-L"/usr/lib64/" -llapack.so.3 -lblas.so.3 ';
options = '-I../include -I../include/NifTI -I../include/LevelSet ';

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
 












