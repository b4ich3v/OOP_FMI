
//	Основи на Компютърната Графика
//	Модел 22211 - Снежинка на Кох
//	П. Бойчев, 2017



// конструктор на модела
MEIRO.Models.M22211 = function M22211(room)
{
	MEIRO.Model.apply(this, arguments);

	this.n = 5;
	this.koch=[];
	for (var i=0; i<this.n; i++)
		this.koch.push( this.generateKochSnowflake(i) );
		
	// бутон за превключване
	var that = this;
	this.state = this.n-1;
	this.toggle = new MEIRO.CornerButton('topLeft', function(){that.onToggle();}, 'НИВО', 'images/n123n.png');
	this.toggle.hide();
	this.toggle.button.onclick();

	// сглобяване на целия модел
	for (var i=0; i<this.n; i++)
		this.image.add(this.koch[i]);
}

MEIRO.Models.M22211.prototype = Object.create(MEIRO.Model.prototype);

MEIRO.Models.M22211.DIST = {MIN:5, MAX:20, HEIGHT:0};
MEIRO.Models.M22211.POS = {DIST:10, ROT_X:Math.PI/2, ROT_Y:0};
MEIRO.Models.M22211.ROT_Y = {MIN:-0.1, MAX:0.7};


// аниматор на модела
MEIRO.Models.M22211.prototype.onAnimate = function(time)
{
	//reanimate();
}



// информатор на модела
MEIRO.Models.M22211.prototype.onInfo = function(element)
{
	var s = '';
	s += '<h1>Снежинка на Кох</h1>';

	s += '<p>Фракталът Снежинка на Кох е съставен от съединени три отсечки на Кох. Началната форма е равностранен триъгълник, като на всяка следващата добавените отсечки са "навън" от фигурата. Лицето на Снежинката на Кох е крайно, но периметърът е безкраен.</p>';
	
	element.innerHTML = s;
}


MEIRO.Models.M22211.prototype.generateKochSnowflake = function(level)
{
	var len = 5,
		n = 0;

	var turtle = new MEIRO.Turtle(0);
	turtle.setPosition(new THREE.Vector3(-len/2,0,-len*Math.sqrt(3)/6));
	
	var koch = new MEIRO.Polygon( 1+3*Math.pow(4,level));
	koch.rotation.x = -Math.PI/2;
	koch.visible = false;
	
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


// превключвател на модела
MEIRO.Models.M22211.prototype.onToggle = function(element)
{
	this.koch[this.state].visible = false;	
	
	this.state = (this.state+1)%this.n;
	this.toggle.setText('НИВО №'+this.state);

	this.koch[this.state].visible = true;	
	
	reanimate();
}
	