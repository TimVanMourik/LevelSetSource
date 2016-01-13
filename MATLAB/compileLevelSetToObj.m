% @todo if the output file cannot be written, it isn't. Fix this to give a
% proper warning.

%%
sourceDirectory = '../src';
allFileNames = 'levelSetToObj.cpp';
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'Volume.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'Volume4D.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'MarchingCubes/GLData.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'MarchingCubes/Position.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'MarchingCubes/BoundingBox.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'MarchingCubes/HashTable.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'MarchingCubes/MarchingCubes.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'MarchingCubes/ObjFactory.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'MarchingCubes/ImplicitObject.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'MarchingCubes/VolumeField.cpp')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'NifTI/nifti1_io.c')];
allFileNames = [allFileNames , ' ' fullfile(sourceDirectory, 'NifTI/znzlib.c')];
allFileNames = [allFileNames , ' '];

%%
libraries = '-L"../lib" -llapack -lblas ';
options = '-I../include -I../include/MarchingCubes  -I../include/NifTI ';
eval(['mex ' allFileNames, libraries, options]);

%% Test with single SDF
sdfFile = 'TestFiles/monkey.sdf.nii';
objFile = 'TestFile/monkey_reconstructed.obj';

levelSetToObj(sdfFile, objFile);
 
%% Test with level set 
levelSetFile = '../../Volumes/brain.layers.nii';
objFile = 'TestFles/BrainLayer.obj';

levelSetToObj(levelSetFile, objFile);
 








