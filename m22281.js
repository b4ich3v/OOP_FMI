
//	Основи на Компютърната Графика
//	Модел 22281 - Питагорово дърво
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22281 = function M22281(room)
{
	MEIRO.Model.apply(this, arguments);

	this.n = 13;
	this.pytha=[];
	//for (var i=0; i<this.n; i++)
	//	this.pytha.push( this.empty );
		
	// бутон за превключване
	var that = this;
	this.state = this.n-1;
	this.toggle = new MEIRO.CornerButton('topLeft', function(){that.onToggle();}, 'НИВО', 'images/n123n.png');
	this.toggle.hide();
	this.toggle.button.onclick();

	// сглобяване на целия модел
	//for (var i=0; i<this.n; i++)
	//	this.image.add(this.pytha[i]);
}

MEIRO.Models.M22281.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22281.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22281.POS = {DIST:10, ROT_X:Math.PI/2, ROT_Y:0};
MEIRO.Models.M22281.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22281.prototype.onAnimate = function(time)
{
	//reanimate();
}



// информатор на модела
MEIRO.Models.M22281.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Питагорово дърво</h1>';

	s += '<p>Този фрактал се генерира като профил на конструкция от квадрати и подобни триъгълници. Започва се с квадрат. На негова страна се поставя триъгълник с долепена до квадрата хипотенуза. На катетите на триъгълника се долепят по-малки квадрати. На тях се долепят триъгълници и т.н.</p>';
	
	element.innerHTML = s;
}


MEIRO.Models.M22281.prototype.generatePythaTree = function(level)
{
	var len = 1.75,
		n = 0;

	var turtle = new MEIRO.Turtle(0);
	turtle.setPosition(new THREE.Vector3(-2*len,0,0.5*len));
	
	var pytha = new MEIRO.Polygon( 1 );
	pytha.rotation.set(-Math.PI/2,-Math.PI/2,0);
	pytha.visible = false;

	function tree(len,angle,level)
	{
		turtle.fd(len);
		pytha.setPoint(n++,turtle.getPosition());
		
		if (level)
		{
			turtle.rt( angle );
			tree( len*Math.cos( angle*Math.PI/180 ),angle,level-1 );
			turtle.rt( 90 );
			tree( len*Math.sin( angle*Math.PI/180 ),angle,level-1 );
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
	tree(len,37.5,level);

	turtle.lt(90);
	turtle.fd(len);
	pytha.setPoint(n++,turtle.getPosition());
	
	return pytha;
}


// превключвател на модела
MEIRO.Models.M22281.prototype.onToggle = function(element)
{
	if (this.pytha[this.state])
		this.pytha[this.state].visible = false;	
	
	this.state = (this.state+1)%this.n;
	this.toggle.setText('НИВО №'+this.state+' от '+(this.n-1));

	if (!this.pytha[this.state])
	{
		this.pytha[this.state] = this.generatePythaTree(this.state);
		this.image.add(this.pytha[this.state]);
	}
	
	this.pytha[this.state].visible = true;	
	
	reanimate();
}
	