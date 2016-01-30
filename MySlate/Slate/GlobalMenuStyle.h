// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SlateWidgetStyleContainerBase.h"
#include "SlateWidgetStyle.h"
#include "SlateBasics.h"
#include "GlobalMenuStyle.generated.h" 

// Provides a group of global style settings for our game menus! 
USTRUCT()
struct FGlobalStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()
		// Stores a list of Brushes we are using (we aren't using any) into OutBrushes.
		virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;

	// Stores the TypeName for our widget style.
	static const FName TypeName;

	// Retrieves the type name for our global style, which will be used by our Style Set to load the right file. 
	virtual const FName GetTypeName() const override;

	// Allows us to set default values for our various styles. 
	static const FGlobalStyle& GetDefault();

	// Style that define the appearance of all menu buttons. 
	UPROPERTY(EditAnywhere, Category = Appearance)
		FButtonStyle MenuButtonStyle;

	// Style that defines the text on all of our menu buttons. 
	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle MenuButtonTextStyle;

	// Style that defines the text for our menu title. 
	UPROPERTY(EditAnywhere, Category = Appearance)
		FTextBlockStyle MenuTitleStyle;
};

// Provides a widget style container to allow us to edit properties in-editor
UCLASS(MinimalAPI)
class UGlobalMenuStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_UCLASS_BODY()

public:
	// This is our actual Style object. 
	UPROPERTY(EditAnywhere, Category = Appearance, meta = (ShowOnlyInnerProperties))
		FGlobalStyle MenuStyle;

	// Retrievs the style that this container manages. 
	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&MenuStyle);
	}
};
