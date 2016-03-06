#include "MySlate.h"
#include "StandardSlateWidget.h"
#include "StandardHUD.h"

#include "GlobalMenuStyle.h" 
#include "MenuStyles.h" 

#define LOCTEXT_NAMESPACE "SStandardSlateWidget"
#include "Engine.h"



void SStandardSlateWidget::Construct(const FArguments& InArgs)
{
	OwnerHUD = InArgs._OwnerHUD;
	OnConfirm = InArgs._OnConfirmClicked;

	//加载蓝图style类
	MenuStyle = &FMenuStyles::Get().GetWidgetStyle<FGlobalStyle>("MySlateWidgetStyleAsset");

	//绑定数据到控件上
	Score.Bind(this, &SStandardSlateWidget::GetScore);
	Health.Bind(this, &SStandardSlateWidget::GetHealth);
	_healthCounter = 0.f;
	_scoreCounter = 100.f;
	_bStop = false;

	//--------------------  定义ui控件 begin -----------------
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////If the code below doesn't look like C++ to you it's because it (sort-of) isn't,
	/////Slate makes extensive use of the C++ Prerocessor(macros) and operator overloading,
	/////Epic is trying to make our lives easier, look-up the macro/operator definitions to see why.
	ChildSlot
		.VAlign(VAlign_Fill)
		.HAlign(HAlign_Fill)
		[
			SNew(SOverlay)
			+ SOverlay::Slot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Center)
		[
			SNew(STextBlock)
			.ShadowColorAndOpacity(FLinearColor::Black)
		.ColorAndOpacity(FLinearColor::Red)
		.ShadowOffset(FIntPoint(-1, 1))
		.Font(FSlateFontInfo("Veranda", 16))
		.Text(LOCTEXT("HelloSlate", "Hello, Slate!"))

		]

	+ SOverlay::Slot() //添加一个节点插槽
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		[
			//The button!//添加按钮
			SAssignNew(RefreshButton, SButton)
			.ButtonStyle(FCoreStyle::Get(), "NoBorder")
		//.OnClicked(this, &SStandardSlateWidget::OnClicked) //调用本类的函数
		.OnClicked(InArgs._OnConfirmClicked) //调用外部的函数
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Center)
		.ForegroundColor(FSlateColor::UseForeground())
		//.DesiredSizeScale(FVector2D(5.f, 5.f))
		.ContentScale(FVector2D(1.5f,1.5f))
		[
			//Colored Background//添加按钮背景
			SNew(SBorder)
			.Padding(FMargin(3))
		.DesiredSizeScale(FVector2D(2.f, 2.f))
		//~~~ Rainbow Image for Button!!! ~~~
		//.BorderImage(FCoreStyle::Get().GetBrush("ColorSpectrum.Spectrum"))
		[
			//Button Text!! AssignNew so can change color later
			SAssignNew(RefreshButtonText, STextBlock)//添加文字
			.Text(FString("Refresh (F5) "))
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/simhei.ttf"), 30.f))
		.ColorAndOpacity(FLinearColor(1, 0, 1, 1))
		.HighlightColor(FLinearColor(1, 1, 0, 1))
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(1, -1))
		]
		]
		]

	+ SOverlay::Slot()
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Center)
		[
			//Resizes the image
			SNew(SBox)
			.WidthOverride(64)
		.HeightOverride(64)
		[
			//~~~ Clear Button / Trash Can ~~~
			SAssignNew(ClearTileButton, SButton)
			.ButtonStyle(FCoreStyle::Get(), "NoBorder")
		.OnPressed(this, &SStandardSlateWidget::OnPressed)
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.ForegroundColor(FSlateColor::UseForeground())
		[
			//Button Content Image
			TSharedRef<SWidget>(SNew(SImage).Image(
			FCoreStyle::Get().GetBrush("TrashCan")
				))
		]
		]
		]

	//测试style用
	+ SOverlay::Slot() //添加一个节点插槽
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Bottom)
		[
			SAssignNew(TestStyleText, STextBlock)//添加文字
			.Text(FString("Test Style"))
			.TextStyle(&MenuStyle->MenuTitleStyle)
		]

	//测试数据绑定用
	+ SOverlay::Slot() //添加一个节点插槽
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Bottom)
		[
			SNew(STextBlock)//添加文字
			.Text(Health)
			.TextStyle(&MenuStyle->MenuTitleStyle)
		]
	+ SOverlay::Slot() //添加一个节点插槽
		.HAlign(HAlign_Right)
		.VAlign(VAlign_Bottom)
		[
			SNew(STextBlock)//添加文字
			.Text(Score)
			.TextStyle(&MenuStyle->MenuTitleStyle)
		]

		];
	//--------------------  定义ui控件 end -----------------

	//当鼠标划过时，显示的鼠标样式
	//Set Cursors
	ClearTileButton->SetCursor(EMouseCursor::SlashedCircle);
	RefreshButton->SetCursor(EMouseCursor::Hand);

	//当鼠标滑过时显示的提示
	ClearTileButton->SetToolTip(
		SNew(SToolTip)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("FileTree", "Clear", "Clear any currently Loaded Preview Tile!  -Rama"))
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/simhei.ttf"), 30.f))
		.ColorAndOpacity(FLinearColor(1, 0, 1, 1))
		.HighlightColor(FLinearColor(1, 1, 0, 1))
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(-2, 2))
		]
	);

	RefreshButton->SetToolTip(
		SNew(SToolTip)
		[
			SNew(STextBlock)
			.Text(NSLOCTEXT("FileTree", "Refresh", "Refresh Directory and File Listing, updating to hard drive contents! -Rama"))
		.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/simhei.ttf"), 30.f))
		.ColorAndOpacity(FLinearColor(1, 0, 1, 1))
		.HighlightColor(FLinearColor(1, 1, 0, 1))
		.ShadowColorAndOpacity(FLinearColor::Black)
		.ShadowOffset(FIntPoint(-2, 2))
		]
	);
};

#undef LOCTEXT_NAMESPACE

FReply SStandardSlateWidget::OnClicked()
{

	FString str = FString::Printf(TEXT("--- SStandardSlateWidget::OnClicked hello world - %d"), 123);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, str);

	FReply Result = FReply::Unhandled();
	return Result;
}

void SStandardSlateWidget::OnPressed()
{
	FString str = FString::Printf(TEXT("--- SStandardSlateWidget::OnPressed hello world - %d"), 456);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, str);

	_bStop = _bStop ? false : true;
}

void SStandardSlateWidget::Tick(const FGeometry & AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);

	//每帧检测，如果滑过RefreshButtonText就改变一下颜色
	if (RefreshButtonText->IsHovered())
	{
		RefreshButtonText->SetForegroundColor(FLinearColor(0, 0, 1, 1));
	}
	else
	{
		RefreshButtonText->SetForegroundColor(FLinearColor(1, 0, 1, 1));
	}

	if (!_bStop) //加个停止标记玩玩
	{
		_healthCounter += InDeltaTime;
		_scoreCounter -= InDeltaTime;
	}
}

FText SStandardSlateWidget::GetScore() const
{
	FString str = FString::Printf(TEXT("SCORE:%03.2f"), _scoreCounter);
	return FText::FromString(str);
}

FText SStandardSlateWidget::GetHealth() const
{
	FString str = FString::Printf(TEXT("HEALTH:%03.2f"), _healthCounter);
	return FText::FromString(str);
}
