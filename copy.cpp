/*if (IsKeyDown(KEY_A) && IsKeyDown(KEY_W))
{
	diagonalDown = true;
	amperDiagonal += 0.5;
	if (amperDiagonal < 3)
	{
		this->floatToVector(amperDiagonal);
		this->sendDataTo(this->names.getNMotorCurrentSet(1));
		this->floatToVector(-amperDiagonal);
		this->sendDataTo(this->names.getNMotorCurrentSet(3));
		this->floatToVector(amperStop);
		this->sendDataTo(this->names.getNMotorCurrentSet(2));
		this->sendDataTo(this->names.getNMotorCurrentSet(4));
	}
}
if (IsKeyDown(KEY_D) && IsKeyDown(KEY_W))
{
	diagonalDown = true;
	amperDiagonal += 0.5;
	if (amperDiagonal < 3)
	{
		this->floatToVector(-amperDiagonal);
		this->sendDataTo(this->names.getNMotorCurrentSet(2));
		this->floatToVector(amperDiagonal);
		this->sendDataTo(this->names.getNMotorCurrentSet(4));
		this->floatToVector(amperStop);
		this->sendDataTo(this->names.getNMotorCurrentSet(1));
		this->sendDataTo(this->names.getNMotorCurrentSet(3));
	}
}
*/