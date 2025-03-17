
//	Основи на Компютърната Графика
//	Модел 22282 - Коралово питагорово дърво
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22282 = function M22282(room)
{
	MEIRO.Model.apply(this, arguments);

	this.t = 0;
	this.speed = 0;
	
	this.n = options.lowpoly?8:10;
	this.pytha = new MEIRO.Polygon(1);
	this.pytha.rotation.set(-Math.PI/2,-Math.PI/2,0);
	this.generatePythaTree(this.n);
		
	// бутон за превключване
	var that = this;
	this.state = this.n-1;
	this.toggle = new MEIRO.CornerButton('topLeft', function(){that.onToggle();}, 'СТАРТ', 'images/start.stop.png');
	this.toggle.hide();

	// сглобяване на целия модел
	this.image.add(this.pytha);
}

MEIRO.Models.M22282.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22282.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22282.POS = {DIST:10, ROT_X:Math.PI/2, ROT_Y:0};
MEIRO.Models.M22282.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22282.prototype.onAnimate = function(time)
{
	this.t += this.speed;
	this.generatePythaTree(this.n);
	
	if (this.speed>0.0001)
		reanimate();
		
	TWEEN.update();
}



// информатор на модела
MEIRO.Models.M22282.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Коралово питагорово дърво</h1>';

	s += '<p>Триъгълниците в питагоровото дърво не е задължително да са подобни. Генерирано дърво с неподобни триъгълници е нерегулярно дърво.</p><p>В този модел е показано нерегулярно питагорово дърво, на което триъгълниците се променят динамично &ndash; всеки със свой цикъл във времето.</p>';
	
	element.innerHTML = s;
}


MEIRO.Models.M22282.prototype.generatePythaTree = function(level)
{
	var len = 1,
		n = 0,
		t = this.t;

	var turtle = new MEIRO.Turtle(0);
	turtle.setPosition(new THREE.Vector3(-3*len,0,0.5*len));
	
	var pytha = this.pytha;

	for (var i=0; i<pytha.geometry.vertices.length; i++)
		pytha.geometry.vertices[i].set(0,0,0);
	
	function tree(len,level)
	{
		turtle.fd(len);
		pytha.setPoint(n++,turtle.getPosition());
		
		if (level)
		{
			var angle = 45+25*Math.sin(rpm(t,350)+n+2*Math.cos(20*n-t/300));
			turtle.rt( angle );
			tree( len*Math.cos( angle*Math.PI/180 ),level-1 );
			turtle.rt( 90 );
			tree( len*Math.sin( angle*Math.PI/180 ),level-1 );
			turtle.rt( 90-angle );
		}
		else
		{
			turtle.lt(90);
			turtle.fd(len);
			pytha.setPoint(n++,turtle.getPosition());
			turtle.lt(90);
		}
		
		turtle.fd(len);
		pytha.setPoint(n++,turtle.getPosition());
	}
	
	pytha.setPoint(n++,turtle.getPosition());
	tree(len,level);

	turtle.lt(90);
	turtle.fd(len);
	pytha.setPoint(n++,turtle.getPosition());
}


// превключвател на модела
MEIRO.Models.M22282.prototype.onToggle = function(element)
{
	var that = this;
	new TWEEN.Tween({k:this.speed})
		.to({k:this.speed>0.5?0:1},1000)
		.easing( TWEEN.Easing.Quadratic.InOut )
		.onUpdate( function(){that.speed=this.k} )
		.start();
	reanimate();
}
	