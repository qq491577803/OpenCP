Reference Manual
================
Documents in Japanese for Lab's members
（現在，現状研究室内部専用：以下，研究室内向けメッセージ）
マニュアルは，みんなで更新していってください．  
更新するのを期待して待っても，ほぼ更新されません．
（バグを発見したときについでに更新するくらい）

# core

## checkSameImage.hpp
ランダムサンプルによる同一画像かどうかの確認する関数群
* [class CheckSameImage](checkSameImage.md "class CheckSameImage")
* [checkSameImage](checkSameImage.md "checkSameImage")

## concat.hpp
画像の連結・分解の関数群
* [concat/concatMerge](concat_jp.md "#concat/concatMerge")
* [concatSplit](concat_jp.md "#concatSplit")
* [concatExtract](concat_jp.md "#")

## copyMakeBorder.hpp
cv::copyMakeBorderを高速化した関数群
* [copyMakeBorderReplicate](copyMakeBorder_jp.md "copyMakeBorderReplicate")
* [splitCopyMakeBorder](copyMakeBorder_jp.md "splitCopyMakeBorder")

## count.hpp
画像の画素の属性をカウントする関数群
 * [countNaN](count_jp.md "#countNaN")
 * [countInf](count_jp.md "#countInf")
 * [countDenormalizedNumber](count_jp.md "#countDenormalizedNumber")
 * [countDenormalizedNumberRatio](count_jp.md "#countDenormalizedNumberRatio")

## crop.hpp
画像の切り抜き（クロップ）用関数群
 * [cropZoom](crop_jp.md "#cropZoom")
 * [cropZoomWithBoundingBox](crop_jp.md "#cropZoomWithBoundingBox")
 * [cropZoomWithSrcMarkAndBoundingBox](crop_jp.md "#cropZoomWithSrcMarkAndBoundingBox")
 * [cropZoom](crop_jp.md "#cropCenter")
 * [guiCropZoom](crop_jp.md "#guiCropZoom")

## histogram.hpp
ヒストグラムの描画関数群
 * [drawHistogramImage](histogram_jp.md "#drawHistogramImage")
 * [drawHistogramImageGray](histogram_jp.md "#drawHistogramImageGray")
 * [drawAccumulateHistogramImage](histogram_jp.md "#drawAccumulateHistogramImage")
 * [drawAccumulateHistogramImageGray](histogram_jp.md "#drawAccumulateHistogramImageGray")

## imshowExtension.hpp
imshowの拡張
* [imshowNormalize](imshowExtension_jp.md "imshowNormalize")
* [imshowScale](imshowExtension_jp.md "imshowScale")
* [imshowResize](imshowExtension_jp.md "imshowResize")
* [imshowCountDown](imshowExtension_jp.md "imshowCountDown")

# imgprog
## blend.hpp
2枚の画像の合成関数群
* [alphaBlend](blend_jp.md "#alphaBlend")
* [alphaBlendFixedPoint](blend_jp.md "#alphaBlendFixedPoint")
* [guiAlphaBlend](blend_jp.md "#guiAlphaBlend")
* [dissolveSlideBlend](blend_jp.md "#dissolveSlideBlend")
* [guiDissolveSlideBlend](blend_jp.md "#guiDissolveSlideBlend")

## contrast.hpp
トーンカーブによるコントラスト強調の関数群
* [convert](contrast_jp.md "#convert")
* [cenvertCentering](contrast_jp.md "#cenvertCentering")
* [contrastSToneExp](contrast_jp.md "#contrastSToneExp")
* [contrastGamma](contrast_jp.md "#contrastGamma")
* [quantization](contrast_jp.md "#quantization")
* [guiContrast](contrast_jp.md "#guiContrast")

## Metrics.hpp
画質評価関数群
 * [getPSNR](metrics_jp.md "#getPSNR")
 * [getPSNR_PRECISION](metrics_jp.md "getPSNR_PRECISION")
 * [getPSNR_CHANNEL](metrics_jp.md "#getPSNR_CHANNEL")
 * [class PSNRMetrics](metrics_jp.md "class PSNRMetrics")
 * [localPSNRMap](metrics_jp.md "localPSNRMap")
 * [guiLocalPSNRMap](metrics_jp.md "guiLocalPSNRMap")
 * [getMSE](metrics_jp.md "#getMSE")
 * [getInacceptableRatio](metrics_jp.md "getInacceptableRatio")
 * [getEntropy](metrics_jp.md "#getEntropy")
 * [getTotalVariation](metrics_jp.md "#getTotalVariation")
 * [isSameMat](metrics_jp.md "#isSameMat")
 * SSIM：関数修正中

## detailEnhancement.hpp
詳細強調の関数
* [detailEnhancementBox](detailEnhancement_jp.md "#detailEnhancementBox")
* [detailEnhancementGauss](detailEnhancement_jp.md "#detailEnhancementGauss")
* [detailEnhancementBilateral](detailEnhancement_jp.md "#detailEnhancementBilateral")
* [detailEnhancementGuided](detailEnhancement_jp.md "#detailEnhancementGuided")

# filter
## guidedFilter.hpp
ガイデットフィルタの関数
* [guidedImageFilter](guidedFilter_jp.md "#guidedImageFilter")
* [class GuidedImageFilter](guidedFilter_jp.md "#class GuidedImageFilter")
* [class GuidedImageFilterTiling](guidedFilter_jp.md "#GuidedImageFilterTiling")

## weightedHistogramFilter.hpp
weighted histogram filterの関数
* [weightedHistogramFilter](weightedHistogramFilter_jp.md "weightedHistogramFilter")
* [weightedWeightedHistogramFilter](weightedHistogramFilter_jp.md "weightedWeightedHistogramFilter")
* [weightedModeFilter/weightedModeFilter](weightedHistogramFilter_jp.md "weightedModeFilter/weightedMedianFilter")
* [weightedWeightedModeFilter/weightedWeightedModeFilter](weightedHistogramFilter_jp.md "weightedWeightedModeFilter/weightedWeightedMedianFilter")

# stereo
## StereoBase.hpp
ステレオマッチングの関数
* [class StereoBase](StereoBase.md)
## StereoEval.hpp
ベンチマーク用の評価関数
* [calcBadPixel](StereoEval.md "calcBadPixel")
* [createDisparityALLMask](StereoEval.md "createDisparityALLMask")
* [createDisparityNonOcclusionMask](StereoEval.md "createDisparityNonOcclusionMask")
* [class calcBadPixel](StereoEval.md "class StereoEval")

# memo
Optimization
* Naive：ほとんど最適化されていない素のC++で書かれたコード．
* OpenCV：OpenCVの最適化された処理を可能な限り使った
* SSE：SSEを使って最適化（昔作った関数で更新がされていない．）
* AVX：AVX/AVX2を使って最適化
* AVX512:現在はコメントアウト
* full optimized:最高レベルの最適化
* single:シングルスレッドの挙動のみ
* parallel：OpenCVのparallel_forを使ったマルチコア実装．
* openmp：OpenMPのparallel_for．コンパイル時コード生成になるため，最大パフォーマンスのためにはライブラリをコンパイルしなおす必要あり．
* コメントなし：NaiveかOpenCVのどちらかと思われる．
# Todo
優先すべきドキュメントは下記のデバッグと開発に頻繁に使用する関数群

* Timer
* ConsoleImage
* Stat
* UpdateCheck
* matInfo
* diff
* Plot
* noise
* inlineSIMDFunctions.hpp
* inlineMathFunctions.hpp
* draw
