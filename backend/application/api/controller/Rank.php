<?php
/**
 * FileName: Rank.php
 * Product: Lazy OJ
 * Author: Hu Lang
 * DateTime: 2019/9/27 15:46
 * Email: admin@oibit.cn
 * GitHub: https://github.com/HULANG-BTB
 * Description:
 *
 */


namespace app\api\controller;


use app\common\controller\Base;
use app\api\model\Rank as RankModel;
use think\App;

class Rank extends Base
{

    public function __construct(App $app = null)
    {
        parent::__construct($app);
        $this->Model = new RankModel();
    }

    public function getRankList()
    {
        /**
         * 获取post数据
         */
        $page = $this->request->post('page/d', 1);
        $limit = $this->request->post('limit/d', 15);
        $keyword = $this->request->post('keyword/s', '');

        /**
         * 查询数据
         */
        $result = $this->Model
            ->where(['identify' => 1])
            ->where($keyword !== '' ? 'username' : 1, '=', $keyword !== '' ? $keyword : 1)
            ->page($page, $limit)
            ->field(['uid' => 'id', 'username', 'submit', 'solved'])
            ->order(['solved' => 'desc', 'submit' => 'asc'])
            ->select();

        /**
         * 获取数据总条数
         */
        $count = $this->Model
            ->where(['identify' => 1])
            ->where(isset($keyword) && isset($type) ? $type : 1, '=', $keyword)
            ->count();

        /**
         * 构造返回结果
         */
        $ret = [
            'code' => 1,
            'data' => [
                'total' => $count,
                'page' => $page,
                'limit' => $limit,
                'data' => $result
            ]
        ];
        return json($ret);
    }

}
