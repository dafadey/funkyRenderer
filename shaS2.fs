#version 330

out vec4 FragColor;
  
in vec2 TexCoords;

uniform int mode;
uniform vec2 d;
uniform vec3 view_dir;
uniform vec3 light;
uniform sampler2D nTexture;
uniform sampler2D cTexture;
uniform sampler2D zTexture;

void main()
{
    vec4 c = texture(cTexture, TexCoords);
    vec3 n = texture(nTexture, TexCoords).xyz;
    vec3 h=vec3(0.5,0.5,0.5);
    float z = texture(zTexture, TexCoords).x;
    /*
    if(TexCoords.y < 0.5 && TexCoords.x > 0.5) {
      float s = dot(light, (n-h)*2);
      s = s*s;
      FragColor = c * s;
    }
    else if(TexCoords.y < 0.5 && TexCoords.x <= 0.5)
      FragColor = vec4(n,1);
    else if(TexCoords.y >= 0.5 && TexCoords.x > 0.5)
      FragColor = vec4(z,z,z,1);
    else {
    */
      if(mode == 0 || mode == 1) {
        int avg=1;
        vec3 na=vec3(0,0,0);
        for(int j=-avg;j<avg+1;j++) {
          for(int i=-avg;i<avg+1;i++) {
            vec2 texLoc=TexCoords+vec2(float(i)*d.x,float(j)*d.y);
            if(texture(zTexture, texLoc).x == 1) // out of geometry
              continue;

            vec3 nn = texture(nTexture, texLoc).xyz;
            if(abs(texture(zTexture, texLoc).x - z) < 0.035)
              na += (nn - h) * 2;
            else if (texture(zTexture, texLoc).x - z > 0.035)
              na -= 5.1 * view_dir;
          }
        }
        na = normalize(na);
        if(mode == 1)
          FragColor = vec4(na.x*.5+.5,na.y*.5+.5,na.z*.5+.5,1);
        else {
          float s = dot(light, na);
          s = s > 0 ? s*s : 0;
          FragColor = c * (s * 0.75 + 0.25);
        }
      } else if (mode == 2) {
        float s = dot(light, (n-h)*2);
        s = s > 0 ? s*s : 0;
        FragColor = c * (s * 0.75 + 0.25);
      } else if (mode == 3) {
        FragColor = c;
      } else if (mode == 4) {
        FragColor = vec4(n.x,n.y,n.z,1);
      } else if (mode == 5) {
        FragColor = vec4(z,z,z,1);
      }
    //}
}
