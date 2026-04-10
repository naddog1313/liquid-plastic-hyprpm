precision highp float;
varying vec2 v_texcoord;
uniform sampler2D tex;
uniform float refraction;
uniform float aberration;

void main() {
    vec2 uv = v_texcoord;
    
    // 1. Refraction: Warp the edges like thick molded plastic
    vec2 dist = uv - 0.5;
    vec2 warpedUV = uv + dist * dot(dist, dist) * refraction;

    // 2. Chromatic Aberration: Split colors at the edges
    float r = texture2D(tex, warpedUV + vec2(aberration, 0.0)).r;
    float g = texture2D(tex, warpedUV).g;
    float b = texture2D(tex, warpedUV - vec2(aberration, 0.0)).b;

    // 3. Plastic Gloss: A sharp white "sheen"
    float shine = smoothstep(0.48, 0.5, sin((uv.x + uv.y) * 5.0));
    
    gl_FragColor = vec4(r, g, b, 1.0) + (shine * 0.1);
}
