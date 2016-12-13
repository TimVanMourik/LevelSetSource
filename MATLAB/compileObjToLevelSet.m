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
 
%% Cube
objFile = 'TestFiles/cube.obj';
sdfFile = 'TestFiles/cube.sdf.nii';
x = 3;
y = 3;
z = 3;
dimensions = [x, y, z];
writeMatrix = eye(4);
transformationMatrix = eye(4);
transformationMatrix(1:3, 4) = -1;

makeSignedDistanceField(objFile, sdfFile, dimensions, writeMatrix, transformationMatrix);
[vertices1, faces1] = tvm_importObjFile(objFile);

%% Test with single SDF
sdfFile = 'TestFiles/cube.sdf.nii';
objFile = 'TestFiles/cube_reconstructed.obj';
[vertices2, faces2] = tvm_importObjFile(objFile);

levelSetToObj(sdfFile, objFile);
configuration.i_Volume      = spm_read_vols(spm_vol(sdfFile));
configuration.i_Slice       = 2;
configuration.i_Vertices    = {{vertices1}, {vertices2}};
configuration.i_Faces       = {{faces1}, {faces2}};
tvm_showObjectContourOnSlice(configuration);

%%
upsampleFactor = 5;
upsampleMatrix = eye(4);
upsampleMatrix([1, 6, 11]) = upsampleFactor;
shiftByHalf = [1, 0, 0, 1/2; 0, 1, 0, 1/2; 0, 0, 1, 1/2; 0, 0, 0, 1];
shiftByOne = shiftByHalf ^ 2;
% load transformation information
oldMatrix               = writeMatrix;
oldTransformation       = reshape(spm_imatrix(oldMatrix), [3, 4]);

% convert transformation in seperate transformations
translation = oldTransformation(:, 1)';
rotation    = oldTransformation(:, 2)';
scale       = oldTransformation(:, 3)';
shear       = oldTransformation(:, 4)';

% these are the inner/outer points of the described box
x0 = translation - 1.5 * scale;
x1 = dimensions .* scale + x0;

% these are the new dimensions...
newDimensions   = dimensions * upsampleFactor;
newScale        = scale / upsampleFactor;
% newTranslation  = dimensions / 2 - newScale / 2;
newTranslation  = x0 + 1.5 * newScale;

% ...that make the new matrix
newMatrix = spm_matrix([newTranslation, ...
                        rotation, ...
                        newScale, ...
                        shear]);

makeSignedDistanceField(objFile, sdfFile, dimensions * upsampleFactor, newMatrix, (shiftByHalf \ upsampleMatrix * shiftByHalf) * transformationMatrix);

%%
v = spm_vol(sdfFile);
spm_imatrix(v.mat)

%%
figure
[vertices, faces] = tvm_importObjFile(objFile);
configuration.i_Volume      = spm_read_vols(spm_vol(sdfFile));
configuration.i_Slice       = 5;
configuration.i_Vertices    = {{[vertices ones(size(vertices, 1), 1)]}};
configuration.i_Faces       = {{faces}};
tvm_showObjectContourOnSlice(configuration);




