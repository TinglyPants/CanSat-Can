import { OBJLoader } from "./OBJLoader.js";

var roll
var pitch

function httpGet(theUrl)
{
    var xmlHttp = new XMLHttpRequest()
    xmlHttp.open( "GET", theUrl, false )
    xmlHttp.send( null )
    return xmlHttp.responseText
}

const scene = new THREE.Scene();
const camera = new THREE.PerspectiveCamera(
    30,
    window.innerWidth / window.innerHeight,
    0.1,
    1000
);
const renderer = new THREE.WebGLRenderer();
renderer.setSize( window.innerWidth, window.innerHeight);
document.body.appendChild( renderer.domElement );

// Loading 3D model
const loader = new OBJLoader()
var obj
loader.load('./basic.obj', (object) => {
    scene.add(object)
    obj = object
})

const light = new THREE.HemisphereLight( 0xffffff, 0x080820, 1)
scene.add( light )
camera.position.set(0, 5, 10)
camera.lookAt(new THREE.Vector3(0,1,0))

function animate(){
    requestAnimationFrame(animate)
    let data = httpGet('/data')
    roll = +data.split(',')[0]
    pitch = +data.split(',')[1]
    obj.rotation.x = roll / 57.2957795 // to radians
    obj.rotation.z = pitch / 57.2957795 // to radians
    renderer.render(scene, camera)
}

animate()