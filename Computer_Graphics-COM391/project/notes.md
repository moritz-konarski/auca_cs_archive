# Notes on Project

## Normal Mapping

- interesting texture with normal mapping that has a moving light in it
- use <https://cpetry.github.io/NormalMap-Online/> to get normal maps
- tangent space is used
- file into `/geometries/`
- add tangents and determinants to 

## [Learn OpenGL](https://learnopengl.com/Advanced-Lighting/Normal-Mapping)

- flat surfaces have uniform normal vectors -> glossy look -- these are 
per-surface normal vectors
- we now use a per-fragment normal vector that makes everything look more
realistic
- cost is relatively low compared to the jump in details
- we don't need to change the lighting equation -- just pass the different
normals to it
- we sample a 2D texture to retrieve the per-fragment normal
- the vectors $x,y,z$ components are stored in the images `r, g, b` components

1. take two textures and bind them to the same plane, put a light on it. See
   how it looks. Then add the code from the website and see if it works
