precision highp float;
varying vec2 v_texcoord;
uniform sampler2D tex;
uniform float refraction;
uniform float aberration;
uniform float roughness;
uniform float blur;

void main() {
    vec2 uv = v_texcoord;
    
    // Use 'blur' to offset sampling
    float offset = blur * 0.001;
    
    // Chromatic Aberration with Refraction
    vec2 dist = uv - 0.5;
    vec2 warpedUV = uv + dist * dot(dist, dist) * refraction;

    float r = texture2D(tex, warpedUV + vec2(aberration + offset, 0.0)).r;
    float g = texture2D(tex, warpedUV).g;
    float b = texture2D(tex, warpedUV - vec2(aberration + offset, 0.0)).b;

    // Use 'roughness' to dull the shine
    float shine = smoothstep(0.5 - (roughness * 0.1), 0.5, sin((uv.x + uv.y) * 10.0));
    
    gl_FragColor = vec4(r, g, b, 1.0) + (shine * 0.15);
}
