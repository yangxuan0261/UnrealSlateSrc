// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "StandardHUD.h"

#include "StandardSlateWidget.h"
#include "Char/CharMgr.h"
#include "Char/MyChar.h"
#include "Char/Comp/MyCharDataComp.h"

AStandardHUD::AStandardHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> EnemyTeamHPObj(TEXT("/Game/Slate/EnemyTeamHealthBar"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> BarFillObj(TEXT("/Game/Slate/BarFill"));
	static ConstructorHelpers::FObjectFinder<UFont> customFontObj(TEXT("/Game/Slate/Fonts/simhei"));


	EnemyTeamHPTexture = EnemyTeamHPObj.Object;
	BarFillTexture = BarFillObj.Object;
	customFont = customFontObj.Object;
}

void AStandardHUD::BeginPlay()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////So far only TSharedPtr<SMyUIWidget> has been created, now create the actual object.
	/////Create a SMyUIWidget on heap, our MyUIWidget shared pointer provides handle to object
	/////Widget will not self-destruct unless the HUD's SharedPtr (and all other SharedPtrs) destruct first.

	MyUIWidget = SNew(SStandardSlateWidget)
		.OwnerHUD(this)
		.OnConfirmClicked(FOnClicked::CreateUObject(this, &AStandardHUD::OnConfirmClicked));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Pass our viewport a weak ptr to our widget
	/////Viewport's weak ptr will not give Viewport ownership of Widget
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Set widget's properties as visible (sets child widget's properties recursively)
	MyUIWidget->SetVisibility(EVisibility::Visible);
}

FReply AStandardHUD::OnConfirmClicked()
{
	FString str = FString::Printf(TEXT("--- AStandardHUD::OnConfirmClicked hello world - %d"), 789);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);

	FReply Result = FReply::Unhandled();
	return Result;
}

void AStandardHUD::DrawHUD()
{

	if (!GEngine || !GEngine->GameViewport)
		return;

	FVector2D ViewportSize;
	GEngine->GameViewport->GetViewportSize(ViewportSize);
	mUIScale = ViewportSize.X / 1024.0f;

	DrawActorsHealth();
}

void AStandardHUD::DrawActorsHealth()
{
	const TMap<int32, AMyChar*>& allChars = UCharMgr::GetInstance()->GetAllChars();
	for (TMap<int32, AMyChar*>::TConstIterator Iter = allChars.CreateConstIterator(); Iter; ++Iter)
	{
		float health = Iter->Value->GetDataComp()->GetHealth();
		float healthMax = Iter->Value->GetDataComp()->GetHealthMax();
		DrawHealthBar(Iter->Value, health, health / healthMax, 18 * mUIScale, -20.f);
	}

	//float counter = 30.f;
	//for (FConstPawnIterator Iterator = GetWorld()->GetPawnIterator(); Iterator; ++Iterator)
	//{
	//	AActor* TestChar = Cast<AActor>(*Iterator);
	//	DrawHealthBar(TestChar, counter/100.f, 18 * mUIScale, -20.f);
	//	counter = counter > 100.f ? 98.f : counter += 20.f;
	//}
}

void AStandardHUD::DrawHealthBar(AActor* ForActor, float _health, float HealthPercentage, int32 BarHeight, int32 OffsetY /* = 0 */) const
{
	//GetComponentsBoundingBox：Returns the bounding box of all components in this Actor. //获取Acotr中所有组件的边界盒子box
	FBox BB = ForActor->GetComponentsBoundingBox();
	FVector Center = BB.GetCenter(); //获取box的中心点，坐标
	FVector Extent = BB.GetExtent(); //获取box的范围长度
	//Project：Transforms a 3D world - space vector into 2D screen coordinates. //转换3D世界坐标为2D屏幕坐标
	FVector2D Center2D = FVector2D(Canvas->Project(FVector(Center.X, Center.Y, Center.Z + Extent.Z)));
	float ActorExtent = 40;

	FVector Pos1 = Canvas->Project(FVector(Center.X, Center.Y - ActorExtent * 2, Center.Z + Extent.Z));
	FVector Pos2 = Canvas->Project(FVector(Center.X, Center.Y + ActorExtent * 2, Center.Z + Extent.Z));
	float HealthBarLength = (Pos2 - Pos1).Size2D(); //血条总长度

	UTexture2D* HealthBarTexture = EnemyTeamHPTexture; //红色血条的文理贴图

	float X = Center2D.X - HealthBarLength / 2; 
	float Y = Center2D.Y + OffsetY;
	FCanvasTileItem TileItem(FVector2D(X, Y), HealthBarTexture->Resource, FVector2D(HealthBarLength * HealthPercentage, BarHeight), FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	TileItem.UV1 = FVector2D(HealthPercentage, 1.0f);
	Canvas->DrawItem(TileItem); //画现有的血量

	//Fill the rest of health with gray gradient texture
	X = Center2D.X - HealthBarLength / 2 + HealthBarLength * HealthPercentage;
	Y = Center2D.Y + OffsetY;
	TileItem.Position = FVector2D(X, Y);
	TileItem.Texture = BarFillTexture->Resource;
	TileItem.UV1 = FVector2D(1.0f, 1.0f); //贴图中的纹理坐标
	TileItem.Size = FVector2D(HealthBarLength * (1.0f - HealthPercentage), BarHeight);
	TileItem.SetColor(FLinearColor(0.5f, 0.5f, 0.5f, 1.f));
	Canvas->DrawItem(TileItem); //画失去的血量

	//画文字
	X = Center2D.X - HealthBarLength / 2 - 50;
	Y = Center2D.Y + OffsetY;

	FCanvasTextItem TextItem(FVector2D(X, Y), FText::FromString(FString::SanitizeFloat(_health)), customFont, FLinearColor::Red);
	TextItem.Scale = FVector2D(1.5f, 1.5f);
	TextItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TextItem);
}

