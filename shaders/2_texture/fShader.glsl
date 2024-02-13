#version 460 core

out vec4 FragColor;

in vec3 outColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_rate;

void main() {
  // FragColor = texture(texture2, TexCoord);
  //   FragColor = texture(outTexture, TexCoord) * vec4(outColor, 1.0);
  FragColor =
      mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mix_rate);
  // FragColor = mix(texture(texture1, TexCoord),
  // texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), 1.0);
}