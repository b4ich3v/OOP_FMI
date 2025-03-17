
//	Основи на Компютърната Графика
//	Модел 22213 - Мълнии на Кох
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22213 = function M22213(room)
{
	MEIRO.Model.apply(this, arguments);

	// топки
	this.ballA = new MEIRO.Sphere(0.5);
	this.ballA.position.set(4,0,0);
	this.ballA.material = new THREE.MeshPhongMaterial({color:'silver',shininess:200});
	
	this.ballB = new MEIRO.Sphere(0.5);
	this.ballB.position.set(-4,0,0);
	this.ballB.material = this.ballA.material;
	
	this.level = 5;
	this.lightning = new MEIRO.Polygon(1+Math.pow(4,this.level));
	this.lightning.material = new THREE.LineBasicMaterial({color:'red'});
	this.turtle = new MEIRO.Turtle(0);

	this.generateKochLightning(this.level);
	
	// сглобяване на целия модел
	this.image.add(this.ballA,this.ballB,this.lightning);
}

MEIRO.Models.M22213.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22213.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22213.POS = {DIST:10, ROT_X:Math.PI/2, ROT_Y:0};
MEIRO.Models.M22213.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22213.prototype.onAnimate = function(time)
{
	if (Math.sin(rpm(time,35))>0.3)
	{
		this.lightning.visible = true;
		this.generateKochLightning(this.level);
	}
	else
	{
		this.lightning.visible = false;
	}
	reanimate();
}



// информатор на модела
MEIRO.Models.M22213.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Мълнии на Кох</h1>';

	s += '<p>Когато се рисува отсечка на Кох със случайно избрани ъгли и деления, крайният резултат е случайно начупена отсечка. Въпреки тази случайност, двата края на отсечката са фиксирани в пространството.</p>';
	
	element.innerHTML = s;
}


MEIRO.Models.M22213.prototype.generateKochLightning = function(level)
{
	var len = 8,
		n = 0,
		lightning = this.lightning,
		turtle = this.turtle;

	turtle.basis.reset();
	turtle.setPosition(this.ballB.position);
	
	function kochSegment(len,level)
	{
		if (level)
		{
			var limit = 20+4*level;
			var angle = THREE.Math.randFloat(limit/2,limit)*Math.sign(Math.random()-0.5);
			var spin = THREE.Math.randFloat(0,360);
			var len1 = len/THREE.Math.randFloat(4,10);
			var len2 = (len-2*len1) / Math.cos(angle*Math.PI/180) / 2;

			level--;
			turtle.lr(spin);
			kochSegment(len1,level);
				turtle.lt(angle);
				kochSegment(len2,level);
				turtle.rt(2*angle);
				kochSegment(len2,level);
				turtle.lt(angle);
			kochSegment(len1,level);
			turtle.lr(-spin);
			
			turtle.basis.x.normalize();
			turtle.basis.y.normalize();
			turtle.basis.z.normalize();
		}
		else
		{
			turtle.fd(len);
			lightning.setPoint(n++,turtle.getPosition());
		}
	}
	
	lightning.setPoint(n++,turtle.getPosition());
	kochSegment(len,level);
}