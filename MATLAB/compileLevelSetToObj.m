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

%%
sdfFile = 'TestFiles/monkey.sdf.nii';
objFile = 'TestFiles/monkey_reconstructed.obj';

levelSetToObj(sdfFile, objFile);
 
%%
levelSetFile = '../../Volumes/brain.layers.nii';
objFile = 'TestFiles/BrainLayer.obj';

levelSetToObj(levelSetFile, objFile);
 








