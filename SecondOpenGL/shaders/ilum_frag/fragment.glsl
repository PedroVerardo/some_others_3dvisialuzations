in data {
vec3 view;
vec3 normal;
vec3 light;
vec2 texcoord;
}f;
out vec4 color;
void main(void)
{
vec3 view = normalize(f.view);
vec3 normal = normalize(f.normal);
vec3 light = normalize(f.light);
float ndotl = dot(normal , light);
color = ( mamb*lamb + mdif * ldif * max (0 , ndotl)) * texture(decal, f.texcoord);
if ( ndotl > 0) {
vec3 refl = normalize(reflect(-light,normal)) ;
color += mspe*lspe*pow(max(0 , dot( refl, view)) , mshi);
}
float fog = exp( -pow( fdensity*(-f.pos.z),2));
color = fog*color+(1-fog)*fcolor;
}


