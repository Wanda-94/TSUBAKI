#include <window/window.h>
#include <utility/initializer.h>
#include <Eigen/Core>
#include <cmath>
#include <component/transform.h>

int main(int argc,char** argv)
{
	Initializer::InitEngine();
	Window* curr_window = new Window();
	curr_window->SetAsCurrentWindow();
	Eigen::Vector4f clear_color = Eigen::Vector4f(0.0f,0.0f,0.0f,1.0f);
	Eigen::Vector4f clear_color_add =  Eigen::Vector4f(0.01f,0.01f,0.01f,0.0f);
	Transform t1;
	Eigen::AngleAxisf r = Eigen::AngleAxisf(45.0f,Eigen::Vector3f(1.0f,0.0f,0.0f));
	Eigen::Quaternionf rq = Eigen::Quaternionf(r);
	Transform t2(Eigen::Vector3f(1.0f,2.0f,3.0f),rq,Eigen::Vector3f(3.0f,4.0f,5.0f));
	t1.SetTransformMatrix(t2.GetTransformMatrix());

	while(curr_window->GetCurrFrameCount()<1000)
	{
		clear_color = clear_color + clear_color_add;
		std::cout << "Frame Count : " <<curr_window->GetCurrFrameCount() << std::endl;
		std::cout << "FPS : " <<1.0f/curr_window->GetCurrDeltaTime()<<std::endl;
		curr_window->UpdateFrame(sin(clear_color[0]), sin(clear_color[1]), sin(clear_color[2]), (clear_color[3]));
	}
	curr_window->CloseWindow();
	Initializer::EndEngine();
	return 0;
}