
//	Основи на Компютърната Графика
//	Модел 22212 - Анимация със снежинки на Кох
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22212 = function M22212(room)
{
	MEIRO.Model.apply(this, arguments);

	this.n = options.lowpoly?20:50;
	
	this.koch=[];
	this.koch.push( this.generateKochSnowflake(3) );

	for (var i=1; i<this.n; i++)
	{
		this.koch.push(new THREE.Line(
			this.koch[0].geometry,
			new THREE.LineBasicMaterial( {
						color: new THREE.Color().setHSL(i/this.n,1,0.5),
					})
		));
		this.koch[i].rotation.copy(this.koch[0].rotation);
		this.koch[i].scale.setScalar(1+1.5*i);
	}
	
	// сглобяване на целия модел
	for (var i=0; i<this.n; i++)
		this.image.add(this.koch[i]);
}

MEIRO.Models.M22212.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22212.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22212.POS = {DIST:10, ROT_X:Math.PI/2, ROT_Y:0};
MEIRO.Models.M22212.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22212.prototype.onAnimate = function(time)
{
	for (var i=0; i<this.n; i++)
	{
		this.koch[i].rotation.y = 2*Math.sin(rpm(time,10)-i/20);
	}
	reanimate();
}



// информатор на модела
MEIRO.Models.M22212.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Анимация със снежинки на Кох</h1>';

	s += '<p>Тази анимация показва '+this.n+' вложени снежинкина Кох. Въртенето на всяка от тях е едно и също, но е отместено леко във времето.</p>';
	
	element.innerHTML = s;
}


MEIRO.Models.M22212.prototype.generateKochSnowflake = function(level)
{
	var len = 0.1,
		n = 0;

	var turtle = new MEIRO.Turtle(0);
	turtle.setPosition(new THREE.Vector3(-len/2,0,-len*Math.sqrt(3)/6));
	
	var koch = new MEIRO.Polygon( 1+3*Math.pow(4,level));
	koch.rotation.x = -Math.PI/2;
	
	function kochSegment(len,level)
	{
		if (level)
		{
			len /= 3;
			level--;
			kochSegment(len,level);
			turtle.lt(60);
			kochSegment(len,level);
			turtle.rt(120);
			kochSegment(len,level);
			turtle.lt(60);
			kochSegment(len,level);
		}
		else
		{
			turtle.fd(len);
			koch.setPoint(n++,turtle.getPosition());
		}
	}
	
	koch.setPoint(n++,turtle.getPosition());
	kochSegment(len,level);
	turtle.rt(120);
	kochSegment(len,level);
	turtle.rt(120);
	kochSegment(len,level);
	
	return koch;
}