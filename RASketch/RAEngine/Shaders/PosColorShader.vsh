attribute vec4 aColor;
attribute vec4 aPosition;

varying lowp vec4 vColor;

uniform mat4 uModelViewProjectionMatrix;

void main()
{
    vColor = aColor;
    gl_Position = uModelViewProjectionMatrix * aPosition;
}
