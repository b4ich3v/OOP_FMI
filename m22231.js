
//	Основи на Компютърната Графика
//	Модел 22231 - Драконова крива
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22231 = function M22231(room)
{
	MEIRO.Model.apply(this, arguments);

	this.k = 0;
	
	this.level = options.lowpoly?10:12;
	this.curve = [];
	this.curve.push(this.generateDragonCurve(this.level));
	for (var i=1; i<4; i++)
	{
		this.curve[i] = new THREE.Line(this.curve[0].geometry,this.curve[0].material.clone());
		this.curve[i].rotation.set(-Math.PI/2,i*Math.PI/2,0,'XYZ');
	}
	
	// бутон за превключване
	var that = this;
	this.toggle = new MEIRO.CornerButton('topLeft', function(){that.onToggle();}, 'ВИЖ', 'images/show.hide.png');
	this.toggle.hide();

	// сглобяване на целия модел
	for (var i=0; i<4; i++)
		this.image.add(this.curve[i]);
}

MEIRO.Models.M22231.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22231.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22231.POS = {DIST:10, ROT_X:Math.PI/2, ROT_Y:0};
MEIRO.Models.M22231.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22231.prototype.onAnimate = function(time)
{
	for (var i=0; i<4; i++)
	{
		this.curve[i].position.set(2.5*(1-this.k),1*(1-this.k),0);
		this.curve[i].rotation.set(-Math.PI/2,this.k*i*Math.PI/2,0,'XYZ');
		this.curve[i].material.color.setHSL(this.k*(0.38*i),1,0.5);
		this.curve[i].scale.setScalar(1-this.k/2);
	}
		
	TWEEN.update();

	if (this.k!=0 && this.k!=1)
		reanimate();
}



// информатор на модела
MEIRO.Models.M22231.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Драконова крива</h1>';

	s += '<p>Драконовата крива заема една четвърт от равнината &ndash; т.е. четири драконови криви след подходящо завъртане се допълват точно и покриват цялата равнина.</p>';
	
	element.innerHTML = s;
}


MEIRO.Models.M22231.prototype.generateDragonCurve = function(level)
{
	var len = 0.1,
		n = 0;

	var turtle = new MEIRO.Turtle(0);
	
	var curve = new MEIRO.Polygon(Math.pow(2,level));
	curve.rotation.x = -Math.PI/2;
	
	function cell(swap)
	{
		turtle.fd(len);
		turtle.lt(90*swap);
		curve.setPoint(n++,turtle.getPosition());
	}
	
	function dragon(level,swap)
	{
		if (level)
		{
			dragon( level-1,+swap );
			cell(swap);
			nogard( level-1,-swap );
		}
	}
	
	function nogard(level,swap)
	{
		if (level)
		{
			dragon( level-1,-swap );
			cell(swap);
			nogard( level-1,+swap );
		}
	}
		
	curve.setPoint(n++,turtle.getPosition());
	dragon(level,1);

	return curve;
}


// превключвател на модела
MEIRO.Models.M22231.prototype.onToggle = function(element)
{
	var that = this;
	new TWEEN.Tween({k:that.k})
		.to({k:that.k>0.5?0:1},4000)
		.easing( TWEEN.Easing.Quadratic.InOut )
		.onUpdate( function(){that.k=this.k} )
		.start();
		
	reanimate();
}
	