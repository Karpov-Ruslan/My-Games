uniform sampler2D texture;

void main() {
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    if (color.r == 1) {
        color = vec4(0, 0, 0, 0);
    }

    gl_FragColor = color;
}