#version 410

uniform vec4 lamb;
uniform vec4 ldif;
uniform vec4 lspe;

uniform vec4 mamb;
uniform vec4 mdif;
uniform vec4 mspe;
uniform float mshi;
uniform vec4 fcolor;
uniform float fdensity;

uniform sampler2D decal;

in data {
  vec3 pos;
  vec3 normal;
  vec3 light;
  vec2 texcoord;
} f;

out vec4 color;

void main (void) 
{
  vec3 view = normalize(-f.pos);
  vec3 normal = normalize(f.normal);
  vec3 light = normalize(f.light);
  float ndotl = dot(normal,light);
  vec4 lcolor = textureProj(decal, f.texcoord);
  color = (mamb*lamb + mdif * ldif * lcolor*max(0,ndotl)); 
  if (ndotl > 0) {
    vec3 refl = normalize(reflect(-light,normal));
    color += mspe * lspe*lcolor * pow(max(0,dot(refl,view)),mshi); 
  }
}



