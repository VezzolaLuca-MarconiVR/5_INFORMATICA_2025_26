const canvas = document.getElementById('c');
const ctx = canvas.getContext('2d');
const S = 3;

canvas.width = Math.floor(canvas.offsetWidth / S);
canvas.height = Math.floor(canvas.offsetHeight / S);
const W = canvas.width, H = canvas.height;

const stars = [];
for(let i = 0; i < 100; i++){
  stars.push({
    x: Math.random()*W, y: Math.random()*H,
    size: 1, t: Math.random()*100,
    speed: 0.2 + Math.random()*0.8
  });
}
for(let i = 0; i < 20; i++){
  stars.push({
    x: Math.random()*W, y: Math.random()*H,
    size: 2, t: Math.random()*100,
    speed: 0.5 + Math.random()*1.2
  });
}
for(let i = 0; i < 10; i++){
  stars.push({
    x: Math.random()*W, y: Math.random()*H,
    size: 1, t: Math.random()*100,
    speed: 0.1 + Math.random()*0.4,
    cross: true
  });
}

function loop(){
  ctx.fillStyle = '#000011';
  ctx.fillRect(0, 0, W, H);

  for(let s of stars){
    s.x -= s.speed;
    s.t++;
    if(s.x < 0) { s.x = W; s.y = Math.random()*H; }
    const bright = Math.sin(s.t * 0.12) > 0.2;
    ctx.fillStyle = bright ? '#FFFFFF' : '#8888BB';
    const x = Math.round(s.x), y = Math.round(s.y), sz = s.size;
    ctx.fillRect(x, y, sz, sz);
    if(s.cross){
      ctx.fillRect(x-1, y, 1, 1);
      ctx.fillRect(x+sz, y, 1, 1);
      ctx.fillRect(x, y-1, 1, 1);
      ctx.fillRect(x, y+sz, 1, 1);
    }
  }

  requestAnimationFrame(loop);
}
loop();