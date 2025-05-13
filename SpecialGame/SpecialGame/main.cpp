#include "DxLib.h"
#include "Utility/InputManager.h"
#include "Utility/ResourceManager.h"
#include "Scene/SceneManager.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int)
{
	//��ʃT�C�Y��ύX
	ChangeWindowMode(TRUE);

	//DxLib�������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//����ʂɕ`���s��
	SetDrawScreen(DX_SCREEN_BACK);

	//�}�l�[�W���[�N���X�̏�����
	SceneManager* manager = nullptr;
	ResourceManager* resource = ResourceManager::GetInstance();

	int result = 0;

	try
	{
		//�N���X�𐶐�
		manager = new SceneManager();

		//������
		manager->Initialize();

		//�C���X�^���X��擾
		InputControl* input = InputControl::GetInstance();

		while (ProcessMessage() != -1 && manager->LoopCheck())
		{
			double next_time = GetNowCount();

			//���͏����̍X�V
			input->Update();

			//��ʂ������
			ClearDrawScreen();

			//�V�[���̍X�V
			manager->Update();

			ScreenFlip();

			//�t���[�����[�g�ݒ�
			next_time += ((1.0 / 60.0) * 1000.0);

			//next_time�̐��l������������傫���ꍇ
			if (next_time > GetNowCount())
			{
				//�w�肳�ꂽ���Ԃ����ҋ@����
				WaitTimer(static_cast<int>(next_time) - GetNowCount());
			}
			else
			{
				next_time = GetNowCount();
			}

			//Space�L�[������ꂽ�ꍇ�A���[�v������I������
			if (input->GetKeyPress(KEY_INPUT_ESCAPE))
			{
				break;
			}
		}
	}
	//�G���[��󂯎�����ꍇ
	catch (std::string& error_text)
	{
		//�G���[���b�Z�[�W��\������
		OutputDebugString(error_text.c_str());
		result = -1;
	}

	//�C���X�^���X��폜
	InputControl::DeleteInstance();

	//�ۑ������摜�Ɖ����f�[�^��폜
	resource->UnloadResourceAll();
	resource->UnloadSoundsAll();

	//�V�[���}�l�[�W���[��nullptr�łȂ��Ȃ�
	if (manager != nullptr)
	{
		//�I��������
		manager->Finalize();
		//�폜����
		delete manager;
	}

	DxLib_End();
	return result;
}